#include <iostream>
#include <ncurses.h>
#include "launcher_screen.h"


Home_Screen::Home_Screen(void){
        initscr();
        getmaxyx(stdscr,this->y,this->x);
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLACK);
        init_pair(2,154,COLOR_BLACK);
        keypad(stdscr,TRUE);
        noecho();
        };

void Home_Screen::draw_outer_border(void){
    box(stdscr,0,0);
    wrefresh(stdscr);
    }


void Home_Screen::fetch_max_screen_size(int *x, int *y){
    *x = this->x;
    *y = this->y;
    return;
    }
