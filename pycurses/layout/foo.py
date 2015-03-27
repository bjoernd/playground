#!/usr/bin/python3
#pylint: disable=I0011,C0102,C0103,C0111
import time
import os
import curses

def get_term_size():
    rows, cols = os.popen("stty size", "r").read().split()
    return int(rows), int(cols)


def move_hello(screen):
    curses.curs_set(0)
    rows, cols = get_term_size()

    colstep = (cols-5.0) / rows

    for x in range(rows-1):
        screen.addstr(x, int(x*colstep), "Hello", curses.A_STANDOUT)
        screen.refresh()
        time.sleep(0.05)
        screen.addstr(x, int(x*colstep), "         ")
    screen.addstr(2,2,"Press a key", curses.A_BOLD)
    screen.getch(0, 0)


def test_colors(screen):
    curses.curs_set(0)
    screen.bkgd(' ', curses.A_STANDOUT)
    win = curses.newwin(20, 32, 2, 2)
    win.border()
    win.bkgd(' ')
    win.addstr(1, 1, "The quick brown fox jumped ...", curses.color_pair(1))
    win.addstr(2, 1, "The quick brown fox jumped ...", curses.color_pair(1) | curses.A_BOLD)
    win.addstr(3, 1, "The quick brown fox jumped ...", curses.color_pair(2))
    win.addstr(4, 1, "The quick brown fox jumped ...", curses.color_pair(2) | curses.A_BOLD)
    win.addstr(5, 1, "The quick brown fox jumped ...", curses.color_pair(3))
    win.addstr(6, 1, "The quick brown fox jumped ...", curses.color_pair(3) | curses.A_BOLD)
    win.addstr(7, 1, "The quick brown fox jumped ...", curses.color_pair(4))
    win.addstr(8, 1, "The quick brown fox jumped ...", curses.color_pair(4) | curses.A_BOLD)
    win.addstr(9, 1, "The quick brown fox jumped ...", curses.color_pair(5))
    win.addstr(10, 1, "The quick brown fox jumped ...", curses.color_pair(5) | curses.A_BOLD)
    win.addstr(11, 1, "The quick brown fox jumped ...", curses.color_pair(6))
    win.addstr(12, 1, "The quick brown fox jumped ...", curses.color_pair(6) | curses.A_BOLD)
    win.addstr(13, 1, "The quick brown fox jumped ...", curses.color_pair(7))
    win.addstr(14, 1, "The quick brown fox jumped ...", curses.color_pair(7) | curses.A_BOLD)
    win.addstr(15, 1, "The quick brown fox jumped ...", curses.color_pair(8))
    win.addstr(16, 1, "The quick brown fox jumped ...", curses.color_pair(8) | curses.A_BOLD)
    if curses.can_change_color():
        win.addstr(17, 1, "Can change color")
    else:
        win.addstr(17, 1, "Cannot change color")
    win.addstr(18, 1, "Press a key")
    win.refresh()
    win.getch()

def test_windows(screen):
    curses.curs_set(0)
    screen.bkgd(' ', curses.A_STANDOUT)
    rows, cols = get_term_size()

    left_cols = int(cols * 0.75)
    right_cols = cols - left_cols
    top_rows = int(rows * 0.75)
    bottom_rows = rows - top_rows

    win_topleft = curses.newwin(top_rows, left_cols, 0, 0)
    win_topleft.border()
    win_topleft.addstr(0, 4, "[Map Window]", curses.color_pair(5))
    win_topleft.addstr(1, 1, ("Window size: (lines=%d, cols=%d)" % (top_rows, left_cols)))
    y, x = win_topleft.getmaxyx()
    win_topleft.addstr(2, 1, ("Window size (curses): lines = %d, cols = %d" % (y, x)))
    win_topleft.addstr(3, 1, ("Screen size (ssize):  lines = %d, cols = %d" % (rows, cols)))
    y, x = screen.getmaxyx()
    win_topleft.addstr(4, 1, ("Screen size (curses): lines = %d, cols = %d" % (y, x)))
    win_topleft.refresh()

    win_topright = curses.newwin(rows, right_cols, 0, left_cols)
    win_topright.border()
    win_topright.addstr(0, 4, "[Status Window]", curses.color_pair(5))
    win_topright.addstr(1, 1, ("Window size: (l=%d, c=%d)" % (rows, right_cols)))
    win_topright.refresh()

    win_botleft = curses.newwin(bottom_rows, left_cols, top_rows, 0)
    win_botleft.border()
    win_botleft.addstr(0, 4, "[Message Window]", curses.color_pair(5))
    win_botleft.addstr(1, 1, ("Window size: (lines=%d, cols=%d)" % (bottom_rows, left_cols)))
    win_botleft.refresh()

    win_topleft.getch()

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
    #move_hello(screen)
    test_colors(screen)
    test_windows(screen)

curses.wrapper(runfunc)
