#include <unistd.h>
#include <stdbool.h>

#define MAX_FUEL 1000

#define MAX_X 400
#define MAX_Y 80

#define MAX_TORPEDOES 100

#define MAX_INP 10



#define SINGULARITY_WIDTH 5

typedef struct{
    //ship to be controlled by players
    char direction;
    bool thrust;
    int y;
    int x;
    int xVel;
    int yVel;
    int fuel;
    int maxFireRate;
    bool alive;
    int torpedoes;
    int id;
} ship;

typedef struct{
    //torpedoes to be shot out the ship
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
    s->alive=1;
    s->id=num;
    s->torpedoes=MAX_TORPEDOES;

    return s;
}


void calculateDirection(int dir, int* x, int* y, int scalar){
    switch(dir){
            case(0):
                *y+=scalar;
                break;
            case(1):
                *y+=scalar;
                *x-=scalar*2;
                break;
            case(2):
                *x-=scalar*2;
                break;
            case(3):
                *y-=scalar;
                *x-=scalar*2;
                break;
            case(4):
                *y-=scalar;
                break;
            case(5):
                *y-=scalar;
                *x+=scalar*2;
                break;
            case(6):
                *x+=scalar*2;
                break;
            case(7):
                *y+=scalar;
                *x+=scalar*2;
                break;
        }
}


void calculateThrust (ship* s){
    //calculates thrust by checking fuel is there and capping it at 3
    if(s->thrust==1 && s->fuel>0){
        --s->fuel;
        calculateDirection(s->direction, &s->xVel, &s->yVel, 1);
        if(s->xVel<=-3){
            s->xVel=-2;
        }else if(s->xVel>=3){
            s->xVel=2;
        }

        if(s->yVel<=-3){
            s->yVel=-2;
        }else if(s->yVel>=3){
            s->yVel=2;
        }
    }
}

void calculateMovement(ship* s, int frame, ship* s0){
    //calculates gravity for ship
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
    //checks collisions for ship - wall, black hole, enemy ship
    if(0>s->y || MAX_Y<s->y || 0>s->x || MAX_X < s->x || (abs(s->x-(MAX_X/2))<((SINGULARITY_WIDTH*2)-2) && abs(s->y-(MAX_Y/2))<(SINGULARITY_WIDTH-1)) || ((abs(s->x-s0->x)<3 && abs(s->y-s0->y)<2))){
        s->alive=0;
    }
    
}

torpedo** setupTorpedoArray(){
    //creates array of torpedo pointers on heap
    torpedo** arr = malloc(sizeof(torpedo*)*MAX_TORPEDOES);

    for(int i=0; i<MAX_TORPEDOES; ++i){
        //creates each torpedo on the heap and sets x to 9999 indicating that it is not been shot
        arr[i] = malloc(sizeof(torpedo));
        arr[i]->direction = -1;
        arr[i]->x=9999;
        arr[i]->y=9999;
    }

    return arr;
}

void createTorpedo(torpedo** arr, ship* s){
    //finds the next free torpedo to use
    for(int i=0; i<MAX_TORPEDOES; ++i){
        if(arr[i]->x==9999){
            //moves to map
            arr[i]->direction = s->direction;
            arr[i]->x=s->x;
            arr[i]->y=s->y;
            calculateDirection(s->direction, &arr[i]->x, &arr[i]->y, 2);
            return;
        }
    }
}

void updateTorpedos(torpedo** torpedoArray, ship* s1, ship* s2){
    for(int i=0; i<MAX_TORPEDOES; ++i){
        torpedo* torp = torpedoArray[i];
        if(torp->x!=9999){
            //move and check if out of bounds
            calculateDirection(torp->direction, &torp->x, &torp->y, 2);
            if(0>torp->y || MAX_Y<torp->y || 0>torp->x || MAX_X < torp->x){
                torpedoArray[i]->x=9999;
                continue;
            }

            mvprintw(torp->y, torp->x, "*");

            //check for any collisions
            if(abs(s1->x-torp->x)<3 && abs(s1->y-torp->y)<2){
                printf("ship 1 dead");
                s1->alive=0;
            }
            if(abs(s2->x-torp->x)<3 && abs(s2->y-torp->y)<2){
                printf("%d    \n",s2->x-torp->x);
                s2->alive=0;
            }

            //checks if two torpedoes are colliding
            for(int j=0; j<MAX_TORPEDOES; ++j){
                if(torpedoArray[j]->x==torpedoArray[i]->x && torpedoArray[j]->y==torpedoArray[i]->y && torpedoArray[i] != torpedoArray[j]){
                    torpedoArray[i]->x=9999;
                    torpedoArray[j]->y=9999;    
                }
            }
        }
    }
}

void checkInput(char key, ship *s1, ship *s2, torpedo** ta){

    switch(key){
        //input keys (top half for player 1, bottom half for player 2)
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
            if(s1->torpedoes>0){
                --s1->torpedoes;
                createTorpedo(ta,s1);
            }
            break;

        case('j'):
            s2->direction=(s2->direction-1<0) ? (7) : (s2->direction-1);
            break;
        case('l'):
            s2->direction=(s2->direction+1)%7;
            break;
        case('i'):
            s2->thrust=1;
            break;
        case('k'):
            s2->thrust=0;
            break;
        case('o'):
            if(s2->torpedoes>0){
                --s2->torpedoes;
                createTorpedo(ta,s2);
            }
            break;

    }
}

void input(ship *s1, ship *s2, torpedo** ta){
    int inputChrs[MAX_INP];
    int ptr =0;
    char alreadyIn;

    //checks the pressed keys 1000 times to allow for multiple inputs for one frame and puts them in an array
    //if a key pressed is not in the array then it inputs it
    for(int i=0; i<1000; ++i){
        int ch = getch();
        if(ch!=-1){
            alreadyIn = 0;
            for(int j=0; j<ptr; ++j){
                if (inputChrs[j]==ch){
                    alreadyIn=1;
                }
            }
            if(alreadyIn==0){
                inputChrs[ptr]=ch;
                ++ptr;
                checkInput(ch, s1, s2, ta);
            }
        }
    } 
}