#include <ncurses.h>
#include <focus.h>

void focus_shift(FOCUS curr, WINDOW *win, WINDOW *win_sec){
    wattron(win,COLOR_PAIR(2));
    box(win,0,0);
    wattroff(win,COLOR_PAIR(2));
    wattron(win_sec,COLOR_PAIR(1));
    box(win_sec,0,0);
    wattroff(win_sec,COLOR_PAIR(1));
    wrefresh(win);
    wrefresh(win_sec);

    }
