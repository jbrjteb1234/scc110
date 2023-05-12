#include <math.h>
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



//void move (ship* s){
    
//}

void thrustShip(ship *s){
    switch(s->direction){
        case(0):
            ++s->y;
            break;
        case(1):
            s->x+=-2;
            ++s->y;
            break;
        case(2):
            s->x+=-2;
            break;
        case(3):
            s->x+=-2;
            --s->y;
            break;
        case(4):
            --s->y;
            break;
        case(5):
            s->x+=2;
            --s->y;
            break;
        case(6):
            s->x+=2;
            break;
        case(7):
            s->x+=2;
            ++s->y;
            break;
    }
}