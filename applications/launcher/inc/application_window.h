#pragma once
#include "window.h"
#include <ncurses.h>

#define MAX_APPLICATIONS 5

typedef struct{
    int app_n;
    std::string name;
    }application;

extern application app_list[];

class ApplicationWindow : public Window{
    private:
        int innerwin_width;
        int innerwin_height;
        int innerwin_startx;
        int innerwin_starty;
        WINDOW *innerWin;
        int currentSelection;

    public:
        ApplicationWindow(int height, int width, int start_x, int start_y);

        void loadApplication(void);

        void handleInput(int input) override;
};