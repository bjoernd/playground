#!/usr/bin/python3
#pylint: disable=I0011,C0102,C0103,C0111,C0301,C0326,R0913

import curses
import time

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

        self.title_spacing = 2
        self.title = ""
        self.title_style = None

        self.win.border()

    def clear(self):
        self.win.clear()
        self.win.border()
        self.paintTitle()

    def refresh(self):
        """Refresh the window after drawing."""
        self.win.refresh()

    def getch(self):
        """Get input character."""
        return self.win.getch()

    def setTitle(self, title, style = None):
        """Set the window title.

        The title will be rendered into the top border. The title
        will be cut short if the window is too narrow. """
        if len(title) < (self.width - 2 * self.title_spacing - 4):
            self.title = "[" + title + "]"
        else:
            self.title = "[" + title[:self.width-2*self.title_spacing - 4] + "..]"
        self.title_style = style

        self.paintTitle()

    def paintTitle(self):
        if self.title_style is None:
            self.win.addstr(0, self.title_spacing, self.title)
        else:
            self.win.addstr(0, self.title_spacing, self.title, self.title_style)

    @property
    def Width(self):
        """Window width in characters"""
        return self.width

    @property
    def Height(self):
        """Window height in characters"""
        return self.height


class LogWindow(Window):
    """A specialized window that collects a list of log messages, renders
       the most recent ones by default and allows scrolling through older
       messages."""
    def __init__(self, screen, width, height, posx, posy):
        super(LogWindow, self).__init__(screen, width, height, posx, posy)
        self.messages            = [] # list of messages
        self.first_msg_on_screen = -1 # -1   -> log last N messages that fit
                                      # >=0  -> log messages starting at msg N
        self.win.keypad(1)

    class LogMessage(object):
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


    def log(self, message, style = None):
        """Log a new message."""
        m = LogWindow.LogMessage(message, style)
        self.messages.append(m)
        # new msg always scrolls down
        self.first_msg_on_screen = -1

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

        # We iterate over all messages, see how many lines they occupy
        # and then fit as many messages as possible into the screen.
        # Behavior depends on scroll state: if we are unscrolled, try
        # to fit as many messages as possible from the end of the msg list.
        # In scrolled state, start fitting from the first_msg_on_screen

        if self.first_msg_on_screen >= 0:
            msg_candidates = self.messages[self.first_msg_on_screen:]
        else:
            msg_candidates = reversed(self.messages)

        for msg in msg_candidates:
            lines_for_msg = int(1 + msg.Length / self.max_chars_per_line())
            printed_lines += lines_for_msg
            if printed_lines > self.max_lines():
                break
            num_msg += 1

        return num_msg


    def write_line_with_style(self, line, style, lineno):
        """Write a single line of message text into line given by
           <lineno> and apply the given <style>."""
        if style is None:
            self.win.addstr(lineno, 1, line)
        else:
            self.win.addstr(lineno, 1, line, style)


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
        if self.first_msg_on_screen == -1:
            new_offs = len(self.messages) - current_msgs + offset
        else:
            new_offs = self.first_msg_on_screen + offset

        if new_offs < 0:
            new_offs = 0

        if new_offs > len(self.messages) - current_msgs:
            new_offs = -1

        self.first_msg_on_screen = new_offs
        self.refresh()

    def refresh(self):
        """Redraw the message window"""
        num_messages = self.fit_messages()
        self.clear()
        if num_messages > 1:
            lineno = 1 # start at line 1 (0 is window border / title)

            if self.first_msg_on_screen < 0: # non-scrolled
                printed_msgs = self.messages[-num_messages:]
            else:
                printed_msgs = self.messages[self.first_msg_on_screen:self.first_msg_on_screen+num_messages]

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

    w.log("This is a very first test message.")
    w.log("This is a totally bold test message.", curses.A_BOLD)
    w.log("This is an extremely (as in TU Dresden green) green test message.", colorManager.color("green"))
    w.refresh()

    for i in range(30):
        w.log("[%d] height %d" % (i, w.max_lines()), colorManager.color("white"))
        w.refresh()
        time.sleep(.1)

    w.log("Press any key...")
    w.refresh()

    while True:
        c = w.getch()
        if c == curses.KEY_PPAGE:
            w.scroll(-2)
            w.refresh()
        elif c == curses.KEY_NPAGE:
            w.scroll(2)
            w.refresh()
        else:
            break


if __name__ == "__main__":
    curses.wrapper(main)
