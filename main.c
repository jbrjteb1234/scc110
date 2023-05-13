#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

#include "entities.h"
#include "screen.h"

#define FRAME_DELAY 400

#define TEST_RUN 50

void loop(ship* s1){

    for(int i=0; i<TEST_RUN; ++i){
        checkInput(s1);

        drawBorders();
        calculateMovement(s1);
        drawShip(s1);


        refresh();
        flushinp();
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