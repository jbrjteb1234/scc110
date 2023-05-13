#include <math.h>
#include <ncurses.h>
#define MAX_FUEL 5000

#define MAX_X 420
#define MAX_Y 80

#define MAX_TORPEDOS 100

typedef struct{
    int direction;
    int thrust;
    int y;
    int x;
    int maxFuel;
    int fuel;
    int maxFireRate;
} ship;

typedef struct{
    int direction;
    int x;
    int y;
} torpedo;

ship* setupShip(){
    //creates ship on the heap for use across program
    ship* s = malloc(sizeof(ship));
    s->x = round(MAX_X/4);
    s->y = round((MAX_Y*3)/4);
    s->direction=5;
    s->fuel=MAX_FUEL;

    return s;
}

void checkInput(ship *s){
    int ch = getch();

    switch(ch){
        case('a'):
            s->direction=(s->direction-1<0) ? (7) : (s->direction-1);
            break;
        case('d'):
            s->direction=(s->direction+1)%7;
            break;
    }
}

void calculateMovement (ship* s){
    
}