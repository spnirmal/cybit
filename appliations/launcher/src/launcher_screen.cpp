#include <iostream>
#include <ncurses.h>

void draw_outer_border(void){
    box(stdscr,0,0);
    }


void fetch_max_screen_size(int &x, int &y){
    getmaxyx(stdscr,y,x);
    return;
    }
