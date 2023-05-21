void setupScreen(){
    initscr();
    timeout(0);
    curs_set(0);
}


void drawBorders(){//draws a border of hashtags and prints the singularity
    for(int i=0; i<=MAX_Y; ++i){
        mvprintw(i,0,"#");
        mvprintw(i,MAX_X,"#");
    }
    for(int i=0; i<=MAX_X; ++i){
        mvprintw(0,i,"#");
        mvprintw(MAX_Y,i,"#");
    }

    mvprintw((MAX_Y/2)-1, (MAX_X/2)-1, "@@@");
    mvprintw((MAX_Y/2), (MAX_X/2)-1, "@@@");
    mvprintw((MAX_Y/2)+1, (MAX_X/2)-1, "@@@");
}

void clears(){//clears every square by printing " "
    for(int x=1; x<MAX_X-1; ++x){
        for(int y=1; y<MAX_Y; ++y){
            mvprintw(y,x,"  ");
        }
    }
}

void drawShip(ship* s){
    int x = s->x;
    int y = s->y;
    mvprintw(y, x, "O");
    switch(s->direction){
        case(0):
            mvprintw(y-1, x-2, "# 0 #");
            mvprintw(y+1, x, "0");
            break;
        case(1):
            mvprintw(y-1, x, "# 0");
            mvprintw(y, x+2, "#");
            mvprintw(y+1, x-2, "0");
            break;
        case(2):
            mvprintw(y, x-2, "0");
            mvprintw(y-1, x+2, "#");
            mvprintw(y+1, x+2, "#");
            mvprintw(y, x+2, "0");
            break;
        case(3):
            mvprintw(y-1, x-2, "0");
            mvprintw(y, x+2, "#");
            mvprintw(y+1, x, "# 0");
            break;
        case(4):
            mvprintw(y-1, x, "0");
            mvprintw(y+1, x-2, "# 0 #");
            break;
        case(5):
            mvprintw(y-1, x+2, "O");
            mvprintw(y+1, x-2, "0 #");
            mvprintw(y, x-2, "#");
            break;
        case(6):
            mvprintw(y, x-2, "0");
            mvprintw(y-1, x-2, "#");
            mvprintw(y+1, x-2, "#");
            mvprintw(y, x+2, "0");
            break;
        case(7):
            mvprintw(y+1, x+2, "0");
            mvprintw(y, x-2, "#");
            mvprintw(y-1, x-2, "0 #");
            break;
    }
}

void drawTorpedos(torpedo** torpArray){
    for(int i=0; i<MAX_TORPEDOS; ++i){
        if(torpArray[i]!=0){
            mvprintw(torpArray[i]->y, torpArray[i]->x, "*");
        }
    }
}