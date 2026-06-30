#pragma once

class home_screen{ 
    public:
        home_screen(){
            initscr();
        };

        ~home_screen(){
            endwin();
        };

};


void draw_outer_border(void);

void fetch_max_screen_size(int &x, int &y);


