#define MAX_FUEL 5000

#define MAX_X 400
#define MAX_Y 80

#define MAX_TORPEDOS 100

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

ship* setupShip(){
    //creates ship on the heap for use across program
    ship* s = malloc(sizeof(ship));
    s->x = round(MAX_X/4);
    s->y = round((MAX_Y*3)/4);
    s->xVel = 0;
    s->yVel = 0;
    s->direction=5;
    s->fuel=MAX_FUEL;
    s->thrust=0;

    return s;
}





void calculateThrust (ship* s){
    if(s->thrust==1){
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
    if(frame%4==0){
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
    s->x+=s->xVel*2;
    s->y+=s->yVel;
}

torpedo** setupTorpedoArray(){
    torpedo** arr = malloc(sizeof(torpedo*)*MAX_TORPEDOS);
    return arr;
}

void createTorpedo(torpedo** arr, ship* s){
    for(int i=0; i<MAX_TORPEDOS; ++i){
        if(arr[i]==0){
            printf("Creating torpedo!");
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
        if(0>=(torp->x)>=MAX_X || 0>=(torp->y)>=MAX_Y){
            free(torpedoArray[i]);
            torpedoArray[i]=0;
        }}
    }
}

void checkInput(ship *s, torpedo** ta){
    int ch = getch();
    s->thrust=0;

    switch(ch){
        case('a'):
            s->direction=(s->direction-1<0) ? (7) : (s->direction-1);
            break;
        case('d'):
            s->direction=(s->direction+1)%7;
            break;
        case('w'):
            s->thrust=1;
            --s->fuel;
            break;
        case('e'):
            createTorpedo(ta,s);
    }
}