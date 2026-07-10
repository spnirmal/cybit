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
