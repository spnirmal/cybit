#include <ncurses.h>
#include <focus.h>
#include "window.h"

void focus_shift(Window *curr_focus, Window *remove_focus){
    curr_focus->color_pair(2);
    curr_focus->draw_border();
    curr_focus->color_pair(1);
    remove_focus->color_pair(1);
    remove_focus->draw_border();
    }
