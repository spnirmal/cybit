#include <iostream>
#include <ncurses.h>
#include <launcher_screen.h>
#include <application_window.h>
#include <string>

int main(){
    //draw the outer screen
    home_screen launcher;

    draw_outer_border();
 
    int max_x,max_y;
    fetch_max_screen_size(max_x,max_y);

    WINDOW *app_win = NULL;
    init_app_win(&app_win,max_y,max_x); 
    draw_app_win_border(&app_win);
    
    refresh();
    wrefresh(app_win);
    
    //setup for keypad input
    keypad(stdscr,1);

    int highlight = 0;
    int ch_in = 0; 
    while(1){
        draw_app_selection(&app_win,&highlight,ch_in);
        refresh();
        wrefresh(app_win);
        ch_in = getch();
        }
  
}
