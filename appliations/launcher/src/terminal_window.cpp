#include <ncurses.h>
#include <stdint.h>
#include "terminal_window.h"
#include "window.h"

TerminalWindow::TerminalWindow(int height, int width, int start_x, int start_y): Window(height,width,start_x,start_y){
    
}

void TerminalWindow::handleInput(int input){

}