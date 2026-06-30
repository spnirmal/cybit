#include <iostream>
#include <ncurses.h>

int main(){
  initscr();

  box(stdscr,0,0);
  int y , x;
  getmaxyx(stdscr,y,x);
  WINDOW *table = NULL;

  table = newwin(y-2,x/4,1,1);
  box(table,0,0);
  refresh();
  
  wrefresh(table);

  getch();
  endwin();
}
