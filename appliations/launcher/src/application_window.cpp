#include <iostream>
#include <ncurses.h>

void init_app_win(WINDOW **win,int y,int x){
    
    *win = newwin(y-2,x/4,1,1);
    return;   
    }

void draw_app_win_border(WINDOW **win){
    box(*win,0,0);
    return;
    }

void draw_app_selection(WINDOW **win,int highlight,appplication *app_list){
        
    }
