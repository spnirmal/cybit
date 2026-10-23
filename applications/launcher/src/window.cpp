#include "window.h"
#include "ncurses.h"

Window::Window(int height, int width, int start_x, int start_y){
    this->height = height;
    this->width = width;
    this->start_x = start_x;
    this->start_y = start_y;

    this->win = newwin(height,width,start_y,start_x);
    return;
    }

Window::~Window(){
    delwin(this->win);
    }

void Window::draw_border(void){
    box(win,0,0);
    wrefresh(win);
    }

void Window::color_pair(int pair){
    if(pair == 1){
        wattron(win,COLOR_PAIR(1));
    }
    else if(pair == 2){
        wattron(win,COLOR_PAIR(2));
    }
}

void Window::handleInput(int input){
    
}