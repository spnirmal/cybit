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
    

    getch();
/*    WINDOW *app_border = NULL;
    init_app_border(&app_border,max_y,max_x); 
    draw_app_border(&app_border);
    
    refresh();
    wrefresh(app_border);
    //make another win for apps menu
    WINDOW *app_menu = NULL;
    init_app_menu(&app_menu,max_y,max_x);
    
    //terminal window creation
    WINDOW *terminal = NULL;
    init_term_window(&terminal,max_y,max_y);
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,154,COLOR_BLACK);
    //setup for keypad input
    keypad(stdscr,TRUE);
    noecho();
    int highlight = 0;
    int ch_in = 0; 
    FOCUS focus = APP_WIN;
    focus_shift(focus,app_border,terminal);    
    draw_app_selection(&app_menu,&highlight,ch_in);
    wrefresh(app_menu);
    
    while(1){
                
        ch_in = getch();
        
        switch(ch_in){
            case KEY_LEFT:
                focus = APP_WIN;
                focus_shift(focus,app_border,terminal);
                break;
            case KEY_RIGHT:
                focus = TERM_WIN;
                focus_shift(focus,terminal,app_border);
                break;
            default:
                break;
            }
            
        if(focus == APP_WIN){
            switch(ch_in){
                case (KEY_UP || KEY_DOWN):
                    draw_app_selection(&app_menu,&highlight,ch_in);
                    wrefresh(app_menu);
                    break;
                default:
                    break;
                }
            }
            
        } */
  
}   
