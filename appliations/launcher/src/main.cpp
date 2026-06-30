#include <iostream>
#include <ncurses.h>
#include <launcher_screen.h>
#include <application_window.h>
#include <string>


typedef struct{
    int app_n;
    std::string name;
    }application;

application app_list[4] = {
    {1,"option1"},
    {2,"option2"},
    {3,"option3"},
    {4,"option4"},
    };

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
    int highlight = 0;
    
    while(1){
        draw_app_selection(&app_win,highlight,app_list); 
           
        }
  
    wrefresh(app_win);

    getch();
  
}
