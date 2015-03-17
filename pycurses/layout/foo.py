#!/usr/bin/python3
#pylint: disable=I0011,C0102,C0103,C0111
import time

import curses

def move_hello(screen):
    screen.bkgd('.', curses.A_STANDOUT)
    for x in range(30):
        if x % 3 == 0:
            attr = curses.A_STANDOUT
        elif x % 3 == 1:
            attr = curses.A_REVERSE
        else:
            attr = curses.A_DIM

        screen.addstr(x, x, "Hello", attr)
        screen.refresh()
        time.sleep(0.06)
        screen.addstr(x, x, "     ")
    screen.addstr("Press a key")
    screen.getch(0, 0)


def test_colors(screen):
    win = curses.newwin(12, 32, 2, 2)
    win.border()
    win.bkgd(' ')
    win.addstr(1, 1, "The quick brown fox jumped ...", curses.color_pair(1))
    win.addstr(2, 1, "The quick brown fox jumped ...", curses.color_pair(2))
    win.addstr(3, 1, "The quick brown fox jumped ...", curses.color_pair(3))
    win.addstr(4, 1, "The quick brown fox jumped ...", curses.color_pair(4))
    win.addstr(5, 1, "The quick brown fox jumped ...", curses.color_pair(5))
    win.addstr(6, 1, "The quick brown fox jumped ...", curses.color_pair(6))
    win.addstr(7, 1, "The quick brown fox jumped ...", curses.color_pair(7))
    win.addstr(8, 1, "The quick brown fox jumped ...", curses.color_pair(8))
    if curses.can_change_color():
        win.addstr(9, 1, "Can change color")
    else:
        win.addstr(9, 1, "Cannot change color")
    win.addstr(10, 1, "Press a key")
    win.refresh()
    win.getch()

def init_colors():
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
    curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
    curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)
    curses.init_pair(5, curses.COLOR_MAGENTA, curses.COLOR_BLACK)
    curses.init_pair(6, curses.COLOR_CYAN, curses.COLOR_BLACK)
    curses.init_pair(7, curses.COLOR_WHITE, curses.COLOR_BLACK)
    curses.init_pair(8, curses.COLOR_BLACK, curses.COLOR_WHITE)

def runfunc(screen):
    init_colors()
    move_hello(screen)
    test_colors(screen)

curses.wrapper(runfunc)
