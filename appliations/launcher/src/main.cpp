#include <iostream>
#include <ncurses.h>
#include <launcher_screen.h>
#include <application_window.h>
#include <terminal_window.h>
#include <focus.h>
#include <window.h>
#include <string>

int main(){
    //draw the outer screen
    Home_Screen launcher;

    launcher.draw_outer_border();
 
    int max_x,max_y;
    launcher.fetch_max_screen_size(&max_x,&max_y);

    //compute screen size for each window
    int app_height = max_y-2;
    int app_width = max_x/4;
    int app_start_x = 1;
    int app_start_y = 1;

    int term_height = max_y-2;
    int term_width = (max_x-(max_x/4) - 2);
    int term_start_x = app_width + 1;
    int term_start_y = 1;
    
    Window app_Window(app_height,app_width,app_start_x,app_start_y);
    Window terminal_Window(term_height,term_width,term_start_x,term_start_y);
    
    app_Window.draw_border();
    terminal_Window.draw_border();

    // initial focus on application list window
    focus_shift(&app_Window,&terminal_Window);
    int input;

    while(1){
        // enter launcher application loop
        input = getch();
        switch(input){
            case KEY_RIGHT: 
                focus_shift(&terminal_Window,&app_Window);
                break;
            case KEY_LEFT:
                focus_shift(&app_Window,&terminal_Window);
                break;
            default:
                break;
        }

    }
    
  
}   
