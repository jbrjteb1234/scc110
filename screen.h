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

    for(int i=-(SINGULARITY_WIDTH-1)/2; i<SINGULARITY_WIDTH; ++i){
        mvprintw((MAX_Y/2)+i, (MAX_X/2)-(SINGULARITY_WIDTH-1)/2, "@@@@@@@@@@");
    }

    
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
    int t = s->thrust;
    if(s->alive==1){
        mvprintw(y, x, "O");
        switch(s->direction){
        case(0):
            mvprintw(y-1, x-2, "# 0 #");
            mvprintw(y+1, x, "0");
            if(t){
                mvprintw(y-2, x-1, "| |");
            }
            break;
        case(1):
            mvprintw(y-1, x, "# 0");
            mvprintw(y, x+2, "#");
            mvprintw(y+1, x-2, "0");
            if(t){
                mvprintw(y-2, x+2, "/");
                mvprintw(y-1, x+4, "/");
            }
            break;
        case(2):
            mvprintw(y, x-2, "0");
            mvprintw(y-1, x+2, "#");
            mvprintw(y+1, x+2, "#");
            mvprintw(y, x+2, "0");
            if(t){
                mvprintw(y,x+4, "==");
            }
            break;
        case(3):
            mvprintw(y-1, x-2, "0");
            mvprintw(y, x+2, "#");
            mvprintw(y+1, x, "# 0");
            if(t){
                mvprintw(y+1, x+4, "\\");
                mvprintw(y+2, x+2, "\\");
            }
            break;
        case(4):
            mvprintw(y-1, x, "0");
            mvprintw(y+1, x-2, "# 0 #");
            if(t){
                mvprintw(y+2, x-1, "| |");
            }
            break;
        case(5):
            mvprintw(y-1, x+2, "O");
            mvprintw(y+1, x-2, "0 #");
            mvprintw(y, x-2, "#");
            if(t){
                mvprintw(y+2, x-2, "/");
                mvprintw(y+1, x-4, "/");
            }
            break;
        case(6):
            mvprintw(y, x-2, "0");
            mvprintw(y-1, x-2, "#");
            mvprintw(y+1, x-2, "#");
            mvprintw(y, x+2, "0");
            if(t){
                mvprintw(y,x-4,"==");
            }
            break;
        case(7):
            mvprintw(y+1, x+2, "0");
            mvprintw(y, x-2, "#");
            mvprintw(y-1, x-2, "0 #");
            if(t){
                mvprintw(y-2, x-2, "\\");
                mvprintw(y-1, x-4, "\\");
            }
            break;
        }
        int infoXPos = 10;
        int infoYPos = MAX_Y+4;
        if(s->id==2){
            infoXPos+=30;
        }
        mvprintw(infoYPos,infoXPos,"Player%d: ",s->id);
        mvprintw(infoYPos+1, infoXPos,"Fuel: %d. ",s->fuel);
        mvprintw(infoYPos+2, infoXPos,"Torpedos: %d. ", s->torpedoes);
    }
}