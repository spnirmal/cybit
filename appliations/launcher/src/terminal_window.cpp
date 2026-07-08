#include <ncurses.h>
#include <stdint.h>

void init_term_window(WINDOW **win,int x, int y){
    *win = newwin((y-2), 109 , 1 , 38 );
    box(*win,0,0);
    wrefresh(*win);
    return;
   } 
