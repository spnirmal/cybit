#pragma once

#define MAX_APPLICATIONS 4

typedef struct{
    int app_n;
    std::string name;
    }application;

extern application app_list[];

void init_app_border(WINDOW **win,int y,int x);

void draw_app_border(WINDOW **win);

void init_app_menu(WINDOW **win,int y, int x);

void draw_app_selection(WINDOW **win,int *highlight,int input);
