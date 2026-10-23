#pragma once

class Home_Screen{
    private:
        int x;
        int y;

    public:
        Home_Screen();

        ~Home_Screen(){
            endwin();
        };

        void draw_outer_border(void);


        void fetch_max_screen_size(int *x, int *y);

};





