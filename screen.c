#include <ncurses.h>

void setupScreen(){
    initscr();
    curs_set(0);
}


void drawBorders(){
    for(int i=0; i<=MAX_Y; ++i){
        mvprintw(i,0,"#");
        mvprintw(i,MAX_X,"#");
    }
    for(int i=0; i<=MAX_X; ++i){
        mvprintw(0,i,"#");
        mvprintw(MAX_Y,i,"#");
    }

    mvprintw((MAX_X/2)-1, (MAX_Y/2)-1, "@@@");
    mvprintw((MAX_X/2)-1, MAX_Y/2, "@@@");
    mvprintw((MAX_X/2)-1, (MAX_Y/2)+1, "@@@");
}

void clears(){
    delch();
    for(int x=1; x<MAX_X-1; ++x){
        for(int y=1; y<MAX_Y; ++y){
            mvprintw(y,x,"  ");
        }
    }
}

void drawShip(ship* s){
    mvprintw(s->y, s->x, "O");
    mvprintw(s->y-1, s->x+2, "O");
    mvprintw(s->y+1, s->x-2, "O");
    mvprintw(s->y, s->x-2, "#");
    mvprintw(s->y+1, s->x, "#");
}