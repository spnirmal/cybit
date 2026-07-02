#pragma once

#define MAX_APPLICATIONS 4

typedef struct{
    int app_n;
    std::string name;
    }application;

extern application app_list[];

void init_app_win(WINDOW **win,int y,int x);

void draw_app_win_border(WINDOW **win);

void draw_app_selection(WINDOW **win,int *highlight,int input);
