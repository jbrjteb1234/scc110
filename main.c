#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

#include "entities.c"
#include "screen.h"
#include "input.c"

#define TEST_RUN 200
#define FRAME_DELAY 200

void loop(){
    setupScreen();

    ship* ship1 = setupShip(1);
    ship* ship2 = setupShip(2);
    torpedo** torpedoArray = setupTorpedoArray();

    for(int i=0; i<TEST_RUN; ++i){
        executeInputBuffer(ship1,ship2,torpedoArray);

        drawBorders();
        
        calculateThrust(ship1);
        calculateThrust(ship2);
        calculateMovement(ship1,i);
        calculateMovement(ship2,i);
        updateTorpedos(torpedoArray);

        drawTorpedos(torpedoArray);
        drawShip(ship1);
        drawShip(ship2);


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