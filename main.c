#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

#include "entities.c"
#include "screen.h"

#define FRAME_DELAY 400

#define TEST_RUN 50

void loop(){
    setupScreen();

    ship* ship1 = setupShip();
    torpedo** torpedoArray = setupTorpedoArray();

    for(int i=0; i<TEST_RUN; ++i){
        checkInput(ship1,torpedoArray);

        drawBorders();
        
        calculateThrust(ship1);
        calculateMovement(ship1,i);
        updateTorpedos(torpedoArray);

        drawTorpedos(torpedoArray);
        drawShip(ship1);


        refresh();
        flushinp();
        usleep(FRAME_DELAY*1000);
        clears();
    }
    endwin();
}

int main(){
    
    char res;

    printf("Type 'Y' to start.\n");
    scanf("%c\n",&res);

    if (res=='Y' || res=='y'){
        loop();
    }

    return 1;
}