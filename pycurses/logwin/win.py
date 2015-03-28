#!/usr/bin/python3
#pylint: disable=I0011,C0102,C0103,C0111,C0301,C0326,R0913

import curses
import time
import datetime

# DEBUGGING
mylogfile = open("log.txt", "w")

class ColorManager(object):
    """Maintains a mapping from <textual description> of a color
       to the respective curses color pair object.
    """
    def __init__(self):
        self.colors = {}
        self.initColorTable()

    def initColorTable(self):
        curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
        curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
        curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
        curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)
        curses.init_pair(5, curses.COLOR_MAGENTA, curses.COLOR_BLACK)
        curses.init_pair(6, curses.COLOR_CYAN, curses.COLOR_BLACK)
        curses.init_pair(7, curses.COLOR_WHITE, curses.COLOR_BLACK)
        curses.init_pair(8, curses.COLOR_BLACK, curses.COLOR_WHITE)

        self.colors = {
            "red" : 1,
            "green" : 2,
            "yellow" : 3,
            "blue" : 4,
            "magenta" : 5,
            "cyan" : 6,
            "white" : 7,
            "black" : 8
        }


    def color(self, name, bold=False):
        ret = curses.color_pair(self.colors[name])
        if bold:
            ret = ret | curses.A_BOLD
        return ret


class Window(object):
    """Represents a rectangular, bordered window. The window's left upper
       corner is at (posy, posx). The window's size is given by (height, width).
    """
    def __init__(self, screen, width, height, posx, posy):
        self.screen = screen
        self.X      = posx
        self.Y      = posy
        self.height = height
        self.width  = width
        self.win    = curses.newwin(height, width, posy, posx)

        self.win.border()

    def clear(self):
        self.win.clear()
        self.win.border()

    def refresh(self):
        """Refresh the window after drawing."""
        self.win.refresh()

    def getch(self):
        """Get input character."""
        return self.win.getch()

    @property
    def Width(self):
        """Window width in characters"""
        return self.width

    @property
    def Height(self):
        """Window height in characters"""
        return self.height


class LogWindow(Window):
    """A window that collects a list of log messages.

       Logs can be split into multiple streams where each stream is rendered
       into a separate tab/subwindow.

       A single stream renders the most recent ones by default and allows
       scrolling through older messages.
    """
    def __init__(self, screen, width, height, posx, posy):
        super(LogWindow, self).__init__(screen, width, height, posx, posy)
        self.active_stream       = None
        self.logstreams          = { }
        self.win.keypad(1)

        self.title_spacing = 2
        self.title = ""
        self.title_style = None


    class LogStream(object):
        """A list of messages and the corresponding scroll state"""
        def __init__(self):
            self.messages = []
            self.first_msg_on_screen = -1 # -1   -> log last N messages that fit
                                          # >=0  -> log messages starting at msg N

        @property
        def Messages(self):
            return self.messages

        def FirstMsg(self):
            return self.first_msg_on_screen

    class LogMessage(object):
        """A single log message. Stores a style along with it."""
        def __init__(self, msg, style=None):
            self.message = msg
            self.style   = style

        @property
        def Message(self):
            return self.message

        @property
        def Style(self):
            return self.style

        @property
        def Length(self):
            return len(self.message)

    def clear(self):
        super(LogWindow, self).clear()
        self.paintTitle()

    def setTitle(self, title, style = None):
        """Set the window title.

        The title will be rendered into the top border. The title
        will be cut short if the window is too narrow. """
        self.title = title
        self.title_style = style
        self.paintTitle()

    def paintTitle(self):
        data = ["[%s" % self.title]
        titles = sorted(self.logstreams.keys())
        for k in titles:
            data.append(" %s" % k)
        data.append("]")
        # We have to print all chars in data + the spaces in between
        total_chars = sum([len(x) for x in data]) + len(data)

        # If our message fits, we go printing and highlight the active stream
        if total_chars < (self.Width - 2 * self.title_spacing):
            col = self.title_spacing
            self.write_string_with_style("[%s" % self.title, 0, col, self.title_style)
            col += (1+len(self.title))
            for k in titles:
                st = self.title_style
                if k == self.active_stream:
                    st = self.title_style ^ curses.A_BOLD
                msg = " %s" % k
                self.write_string_with_style(msg, 0, col, st)
                col += len(msg)
            self.write_string_with_style("]", 0, col, self.title_style)
        else: # try shortening the title
            msg = "[%s ..%s..]" % (self.title, self.active_stream)
            if len(msg) < (self.Width - 2 * self.title_spacing):
                part1 = "[%s .." % self.title
                part2 = "%s" % self.active_stream
                part3 = ".. ]"
                col = self.title_spacing
                self.write_string_with_style(part1, 0, col, self.title_style)
                col += len(part1)
                self.write_string_with_style(part2, 0, col, self.title_style ^ curses.A_BOLD)
                col += len(part2)
                self.write_string_with_style(part3, 0, col, self.title_style)
            else:
                self.write_string_with_style("[XXX title too long]", 0, 1, self.title_style)

    def log(self, message, style = None, stream = None):
        """Log a new message."""
        m = LogWindow.LogMessage(message, style)
        if stream is None:
            if self.active_stream is not None:
                target = self.logstreams[self.active_stream]
            else:
                raise ValueError("Logging without active stream")
        else:
            target = self.logstreams[stream]
        target.Messages.append(m)
        # new msg always scrolls down
        target.first_msg_on_screen = -1

    def log_ts(self, message, style = None, stream = None):
        """Log message adding a timestamp"""
        now = datetime.datetime.now()
        self.log("[%02d.%02d.%04d %02d:%02d:%02d] %s" % \
                 (now.day, now.month, now.year, now.hour, now.minute,
                  now.second, message), style, stream)

    def addStream(self, name):
        self.logstreams[name] = LogWindow.LogStream()

    def deleteStream(self, name):
        if name in self.logstreams.keys():
            self.logstreams.pop(name)
        if self.active_stream == name:
            if len(self.logstreams.keys()) == 0:
                print("WARNING: Removed last existing log stream")
            else:
                self.active_stream = list(self.logstreams.keys())[0]

    def show_stream(self, name):
        if name in self.logstreams.keys():
            self.active_stream = name
        self.refresh()

    def max_chars_per_line(self):
        """Maximum characters that can fit into a line when writing
           messages."""
        return self.width - 5

    def max_lines(self):
        """Maximum #of lines that can be written into this window."""
        return self.height - 2


    def fit_messages(self):
        """Determine the number of messages that fit into the
           visible window area"""
        num_msg       = 0 # number of messages to print
        printed_lines = 0 # number of lines taken by those messages

        msglist = self.logstreams[self.active_stream].Messages

        # We iterate over all messages, see how many lines they occupy
        # and then fit as many messages as possible into the screen.
        # Behavior depends on scroll state: if we are unscrolled, try
        # to fit as many messages as possible from the end of the msg list.
        # In scrolled state, start fitting from the first_msg_on_screen

        if self.logstreams[self.active_stream].FirstMsg() >= 0:
            msg_candidates = msglist[self.logstreams[self.active_stream].FirstMsg():]
        else:
            msg_candidates = reversed(msglist)

        for msg in msg_candidates:
            lines_for_msg = int(1 + msg.Length / self.max_chars_per_line())
            printed_lines += lines_for_msg
            if printed_lines > self.max_lines():
                break
            num_msg += 1

        return num_msg

    def write_string_with_style(self, msg, line, col, style = None):
        if style is None:
            self.win.addstr(line, col, msg)
        else:
            self.win.addstr(line, col, msg, style)


    def write_line_with_style(self, msg, style, lineno):
        """Write a single line of message text into line given by
           <lineno> and apply the given <style>."""
        self.write_string_with_style(msg, lineno, 1, style)


    def write_msg(self, msg, lineno):
        """Write a given message starting in line <lineno>"""
        # Message is split into chunks that are at most as wide as
        # the char_per_line limit
        nchunks = int(msg.Length / self.max_chars_per_line()) + 1

        for c in range(nchunks):
            idx  = c * self.max_chars_per_line()
            data = msg.Message[idx:idx+self.max_chars_per_line()]

            # first line of a message starts with an '*' indicator
            if c == 0:
                lead = '*'
            else:
                lead = ' '

            self.write_line_with_style("%c %s" % (lead, data.lstrip()), msg.Style, lineno + c)

        return nchunks


    def scroll(self, offset):
        current_msgs = self.fit_messages()
        stream = self.logstreams[self.active_stream]
        if stream.FirstMsg() == -1:
            new_offs = len(stream.Messages) - current_msgs + offset
        else:
            new_offs = stream.FirstMsg() + offset

        if new_offs < 0:
            new_offs = 0

        if new_offs > len(stream.Messages) - current_msgs:
            new_offs = -1

        stream.first_msg_on_screen = new_offs
        self.refresh()


    def refresh(self):
        """Redraw the message window"""
        num_messages = self.fit_messages()
        self.clear()
        if num_messages > 1:
            lineno = 1 # start at line 1 (0 is window border / title)
            stream = self.logstreams[self.active_stream]

            if stream.FirstMsg() < 0: # non-scrolled
                printed_msgs = stream.Messages[-num_messages:]
            else:
                printed_msgs = stream.Messages[stream.FirstMsg():stream.FirstMsg() + num_messages]

            for m in printed_msgs:
                lines = self.write_msg(m, lineno)
                lineno += lines

        super(LogWindow, self).refresh()


def main(screen):
    colorManager = ColorManager()

    curses.curs_set(0)

    y, x = screen.getmaxyx()

    w = LogWindow(screen, int(x/2), int(y/3), 1, 1)
    w.setTitle("Log Window", colorManager.color("magenta"))
    w.addStream("1-Logs")
    w.show_stream("1-Logs")
    w.addStream("2-Numbers")

    w.log("This is a very first test message.")
    w.log_ts("And something with a timestamp")
    w.log("This is a totally bold test message.", curses.A_BOLD)
    w.log("This is an extremely (as in TU Dresden green) green test message.", colorManager.color("green") | curses.A_BOLD)
    w.refresh()

    for i in range(30):
        w.log("[%d] height %d" % (i, w.max_lines()), colorManager.color("white"), "2-Numbers")
    w.refresh()

    w.log_ts("<PgUp>   - scroll up", colorManager.color("yellow"), stream="1-Logs")
    w.log_ts("<PgDown> - scroll down", colorManager.color("yellow"), stream="1-Logs")
    w.log_ts("<Alt+1>  - Log Stream", colorManager.color("yellow"), stream="1-Logs")
    w.log_ts("<Alt+2>  - Numbers Stream", colorManager.color("yellow"), stream="1-Logs")
    w.log_ts("q        - Quit", colorManager.color("yellow"), stream="1-Logs")

    while True:
        w.refresh()
        c = w.getch()

        if c == curses.KEY_PPAGE:   # scroll up
            w.scroll(-2)
            w.refresh()
        elif c == curses.KEY_NPAGE: # scroll down
            w.scroll(2)
            w.refresh()
        elif chr(c) == 'n': # add streams to overflow title line
            w.addStream("foobarbaz")
            w.addStream("helloworld")
            w.addStream("highwaytohell")
            w.refresh()
        elif chr(c) == 'q':
            break
        elif c == 27:               # ALT + next char -> select win
            w.win.nodelay(True)
            c2 = w.getch()
            if chr(c2) == '1':
                w.show_stream("1-Logs")
            if chr(c2) == '2':
                w.show_stream("2-Numbers")
            w.win.nodelay(False)
        else:
            break


if __name__ == "__main__":
    curses.wrapper(main)
    mylogfile.close()
