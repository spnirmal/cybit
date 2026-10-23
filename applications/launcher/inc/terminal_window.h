#pragma once

#include <ncurses.h>
#include "window.h"

class TerminalWindow : public Window{
    public :
        TerminalWindow(int height, int width, int start_x, int start_y);

        void handleInput(int input) override;
};
