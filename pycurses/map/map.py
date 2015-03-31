#!/usr/bin/python3
#pylint: disable=I0011,C0102,C0103,C0111,C0301,C0326,R0913

import curses
import cursesui
import sys

MY_DEBUGSTREAM_NAME = "(D)EBUG"

def main(screen):
    cursesui.init_cursesui()
    curses.curs_set(0)
    y,x = screen.getmaxyx()

    if (x < 80) or (y < 25):
        screen.addstr("ERROR: Determined window size: %d rows x %d cols" % (y, x))
        screen.addstr("\nERROR: Need at least 25 x 80")
        screen.getch()
        sys.exit(1)

    log = cursesui.LogWindow(screen, x, int(y/3), 0, 2 * int(y/3)-1)
    log.addStream(MY_DEBUGSTREAM_NAME)
    log.show_stream(MY_DEBUGSTREAM_NAME)

    log.log_ts("Started up. Screen area: %d x %d" % (y, x))
    log.log_ts("Log window dimensions: %d x %d" % (log.Height, log.Width))
    log.getch()

if __name__ == "__main__":
    curses.wrapper(main)
