#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <math.h>

#include "entities.c"
#include "screen.c"

#define FRAME_DELAY 400

#define TEST_RUN 50

void loop(ship* s1){

    for(int i=0; i<TEST_RUN; ++i){
        drawBorders();
        thrustShip(s1);
        //mvprintw(s1->y, s1->x, "O");
        drawShip(s1);


        refresh();
        usleep(FRAME_DELAY*1000);
        clears();
    }
    endwin();
}

void setup(){

    setupScreen();

    ship* ship1 = setupShip();

    loop(ship1);
}

int main(){
    
    char res;

    printf("Type 'Y' to start.\n");
    scanf("%c\n",&res);

    if (res=='Y' || res=='y'){
        setup();
    }

    return 1;
}