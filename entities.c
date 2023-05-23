#include <unistd.h>

#define MAX_FUEL 5000

#define MAX_X 400
#define MAX_Y 80

#define MAX_TORPEDOS 10

#define MAX_INP 10



#define SINGULARITY_WIDTH 5

typedef struct{
    int direction;
    int thrust;
    int y;
    int x;
    int xVel;
    int yVel;
    int maxFuel;
    int fuel;
    int maxFireRate;
} ship;

typedef struct{
    int direction;
    int x;
    int y;
} torpedo;

ship* setupShip(int num){
    //creates ship on the heap for use across program
    ship* s = malloc(sizeof(ship));
    s->x = (num==1) ? round(MAX_X/4) : round((MAX_X*3)/4);
    s->y = (num==1) ? round((MAX_Y*3)/4) : round((MAX_Y)/4);
    s->xVel = 0;
    s->yVel = 0;
    s->direction=(num==1) ? 5 : 1;
    s->fuel=MAX_FUEL;
    s->thrust=0;

    return s;
}





void calculateThrust (ship* s){
    if(s->thrust==1){
        --s->fuel;
        switch(s->direction){
            case(0):
                s->yVel+=1;
                break;
            case(1):
                s->yVel+=1;
                s->xVel-=1;
                break;
            case(2):
                s->xVel-=1;
                break;
            case(3):
                s->yVel-=1;
                s->xVel-=1;
                break;
            case(4):
                s->yVel-=1;
                break;
            case(5):
                s->yVel-=1;
                s->xVel+=1;
                break;
            case(6):
                s->xVel+=1;
                break;
            case(7):
                s->yVel+=1;
                s->xVel+=1;
                break;
        }
        if(s->xVel==-3){
            s->xVel=-2;
        }else if(s->xVel==3){
            s->xVel=2;
        }

        if(s->yVel==-3){
            s->yVel=-2;
        }else if(s->yVel==3){
            s->yVel=2;
        }
    }
}

void calculateMovement(ship* s, int frame){
    if(frame%6==0){
        float xDiff = (s->x-MAX_X/2)/2;
        float yDiff = s->y-MAX_Y/2;
    
        if (xDiff>0){
            s->xVel= (s->xVel>-2)? s->xVel-1 : s->xVel;
        }else{
            s->xVel=(s->xVel<2)? s->xVel+1 : s->xVel;
        }

        if (yDiff>0){
            s->yVel= (s->yVel>-2)? s->yVel-1 : s->yVel;
        }else{
            s->yVel=(s->yVel<2)? s->yVel+1 : s->yVel;
        }
    }
    if(frame%2==0){
        s->x+=s->xVel*2;
        s->y+=s->yVel;
    }
}

torpedo** setupTorpedoArray(){
    torpedo** arr = malloc(sizeof(torpedo*)*MAX_TORPEDOS);
    return arr;
}

void createTorpedo(torpedo** arr, ship* s){
    for(int i=0; i<MAX_TORPEDOS; ++i){
        if(arr[i]==0){
            arr[i] = malloc(sizeof(torpedo));
            arr[i]->direction = s->direction;
            arr[i]->x=s->x;
            arr[i]->y=s->y;
            return;
        }
    }
}

void updateTorpedos(torpedo** torpedoArray){
    for(int i=0; i<MAX_TORPEDOS; ++i){
        torpedo* torp = torpedoArray[i];
        if(torp!=0){
        switch(torp->direction){
            case(0):
                torp->y+=2;
                break;
            case(1):
                torp->y+=2;
                torp->x-=4;
                break;
            case(2):
                torp->x-=4;
                break;
            case(3):
                torp->y-=2;
                torp->x-=4;
                break;
            case(4):
                torp->y-=2;
                break;
            case(5):
                torp->y-=2;
                torp->x+=4;
                break;
            case(6):
                torp->x+=4;
                break;
            case(7):
                torp->y+=2;
                torp->x+=4;
                break;
        }
        if(!(0<(torp->x)<MAX_X) || !(0<(torp->y)<MAX_Y)){
            printf("torpedo out of bounds\n");
            free(torpedoArray[i]);
            torpedoArray[i]=0;
        }}
    }
}

void checkCollisions(ship *s1, ship *s2, torpedo** ta){
    
}

void checkInput(char key, ship *s1, ship *s2, torpedo** ta){

    switch(key){
        case('a'):
            s1->direction=(s1->direction-1<0) ? (7) : (s1->direction-1);
            break;
        case('d'):
            s1->direction=(s1->direction+1)%7;
            break;
        case('w'):
            s1->thrust=1;
            break;
        case('s'):
            s1->thrust=0;
            break;
        case('e'):
            createTorpedo(ta,s1);
            break;
    }
}

void executeInputBuffer(ship *s1, ship *s2, torpedo** ta){
    int inputBuffer[MAX_INP];
    int inputBufferPointer =0;
    char alreadyIn;

    for(int i=0; i<1000; ++i){
        int ch = getch();
        if(ch!=-1){
            alreadyIn = 0;
            for(int j=0; j<inputBufferPointer; ++j){
                if (inputBuffer[j]==ch){
                    alreadyIn=1;
                }
            }
            if(alreadyIn==0){
                inputBuffer[inputBufferPointer]=ch;
                ++inputBufferPointer;
                checkInput(ch, s1, s2, ta);
            }
        }
    } 
}