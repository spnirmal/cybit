#include <iostream>
#include <ncurses.h>
#include <application_window.h>
#include <string>

application app_list[MAX_APPLICATIONS] = {
    {1,"option1"},
    {2,"option2"},
    {3,"option3"},
    {4,"option4"},
    };

void init_app_border(WINDOW **win,int y,int x){
    
    *win = newwin(y-2,x/4,1,1);
    return;   
    }

void draw_app_border(WINDOW **win){
    box(*win,0,0);
    return;
    }

void init_app_menu(WINDOW **win,int y, int x){
    *win = newwin(y-4,(x/4)-2,2,2);
    return;
    }    

void draw_app_selection(WINDOW **win,int *highlight,int input){
        werase(*win);
        switch(input){
            case KEY_UP:
                *highlight = (*highlight-1+MAX_APPLICATIONS)%MAX_APPLICATIONS;
                break;
            case KEY_DOWN:
                *highlight = (*highlight+1+MAX_APPLICATIONS)%MAX_APPLICATIONS;
                break;
            default:
                break;
        }

        for(int i = 0; i < MAX_APPLICATIONS ; i++){
            if(i == *highlight){
                wattron(*win,A_REVERSE);
                mvwprintw(*win,i+1,1,"%s",app_list[i].name.c_str());
                wattroff(*win,A_REVERSE);
            }
            else{
                mvwprintw(*win,i+1,1,"%s",app_list[i].name.c_str());
            }
        } 
        return;
    }

