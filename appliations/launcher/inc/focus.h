#include <ncurses.h>

typedef enum{
    APP_WIN= 1,
    TERM_WIN,
    }FOCUS;


void focus_shift(FOCUS curr, WINDOW *win, WINDOW *win_sec);
