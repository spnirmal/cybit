#ifndef WINDOW_H
#define WINDOW_H
#include "ncurses.h"

class Window{
    private:
        WINDOW *win;
        int width;
        int height;
        int start_x;
        int start_y;

    public:
        Window(int height, int width, int start_x, int start_y);
        ~Window();
        
        void draw_border(void);
    };

#endif

