#include <ncurses.h>
#include "window.h"

typedef enum{
    APP_WIN= 1,
    TERM_WIN,
    }FOCUS;


void focus_shift(Window *curr_focus, Window *remove_focus);
