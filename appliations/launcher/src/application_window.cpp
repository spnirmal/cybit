#include <iostream>
#include <ncurses.h>
#include "window.h"
#include <application_window.h>
#include <string>

application app_list[MAX_APPLICATIONS] = {
    {1,"option1"},
    {2,"option2"},
    {3,"option3"},
    {4,"option4"},
    {5," "},
    };

ApplicationWindow::ApplicationWindow(int height, int width, int start_x, int start_y): Window(height,width,start_x,start_y){
    innerwin_width = width - 1;
    innerwin_height = height - 2;
    innerwin_startx = start_x ;
    innerwin_starty = start_y ;
    innerWin = subwin(win,innerwin_height,innerwin_width,innerwin_starty,innerwin_startx);
    currentSelection = app_list[0].app_n;
    refresh();
    loadApplication();
}


void ApplicationWindow::handleInput(int input){
    switch (input){
        case KEY_UP:
            currentSelection = (currentSelection - 1) % MAX_APPLICATIONS;
            loadApplication();
            break;
        case KEY_DOWN:
            currentSelection = (currentSelection + 1 + MAX_APPLICATIONS) % MAX_APPLICATIONS;
            loadApplication();
            break;
        default:
            break;
    }
}

void ApplicationWindow::loadApplication(void){
    int y_axis = 1;
    int x_axis = 1;
    for(int i = 0 ; i < MAX_APPLICATIONS; i++){
        if(currentSelection == app_list[i].app_n){
            wattron(innerWin,A_REVERSE);
            mvwhline(innerWin, y_axis, x_axis, ' ', getmaxx(innerWin));
            mvwprintw(innerWin,y_axis, x_axis,"%s",app_list[i].name.c_str());
            wattroff(innerWin,A_REVERSE);
        }
        else{
            mvwhline(innerWin,y_axis,x_axis, ' ', getmaxx(innerWin));
            mvwprintw(innerWin,y_axis, x_axis,"%s",app_list[i].name.c_str());
        }
        y_axis++;
    }
    wrefresh(innerWin);
}