#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

#include "entities.c"
#include "screen.h"

#define FRAME_DELAY 200

//main loop - repeats every time the  game is run
int loop(){
    setupScreen();

    ship* ship1 = setupShip(1);
    ship* ship2 = setupShip(2);
    torpedo** torpedoArray = setupTorpedoArray();
    int res=0;
    int fc=0;

    while(1){
        ++fc;
        input(ship1,ship2,torpedoArray);

        drawBorders();
        
        calculateThrust(ship1);
        calculateThrust(ship2);
        calculateMovement(ship1,fc,ship2);
        calculateMovement(ship2,fc,ship1);

        drawShip(ship1);
        drawShip(ship2);

        updateTorpedos(torpedoArray,ship1,ship2);

        refresh();
        flushinp();
        usleep(FRAME_DELAY*1000);
        clears();

        //check if any ship is dead
        if(ship2->alive==0){
            ++res;
        }
        if(ship1->alive==0){
            res+=2;
        }
        if(res>0){
            break;
        }
    }
    endwin();

    free(ship1);
    free(ship2);
    for(int i=0; i<MAX_TORPEDOES; ++i){
        free(torpedoArray[i]);
    }
    free(torpedoArray);

    return res;
}

//starts the round taking the input of the previous scores
void start(int p1, int p2){
    int res = loop();
    char y;
    switch(res){
        case(1):
            printf("Player one wins!\n");
            ++p1;
            break;
        case(2):
            printf("Player two wins!\n");
            ++p2;
            break;
        case(0):
        case(3):
            printf("A tie! No one wins!\n");
            break;
    }
    printf("The score is:\nPlayer1: %d\nPlayer2: %d\nType 'Y' to play again: ",p1,p2);
    scanf(" %c",&y);
    if(y=='Y' || y=='y'){
        timeout(0);
        start(p1,p2);
    }
}

int main(){
    
    char res;

    printf("Type 'Y' to start.\n");
    scanf("%c",&res);

    if (res=='Y' || res=='y'){
        start(0,0);
    }

    return 1;
}
