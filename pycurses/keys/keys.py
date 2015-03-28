#!/usr/bin/python3
#pylint: disable=I0011,C0102,C0103,C0111,C0301,C0326,R0913

import curses

def runfunc(screen):
    screen.keypad(1)
    logfile = open("keys.log", "w")
    while True:
        c = screen.getch()
        logfile.write("KEY: %d (%c)\n" % (c, chr(c)))
    logfile.close()

curses.wrapper(runfunc)
