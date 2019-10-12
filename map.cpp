#include "map.h"

map::map(){
    //the position and color information of each plane
    route = new rectangle[52];
    finalroad = new rectangle[20];
    airport = new rectangle[20];

    route[0].x = startPixX + 14 * recWidth;
    route[0].y = startPixY + 10 * recWidth;
    route[0].color = 0;
    int i = 1;

    for(;i<=3;i++){
        route[i].x = route[i-1].x - recWidth;
        route[i].y = route[i-1].y;
        route[i].color = (route[i-1].color+1)%4;
    }

    route[4].x = route[3].x - recWidth;
    route[4].y = route[3].y + recWidth;
    route[4].color = (route[3].color+1)%4;
    i++;

    for(;i<=7;i++){
        route[i].x = route[i-1].x;
        route[i].y = route[i-1].y + recWidth;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(;i<=13;i++){
        route[i].x = route[i-1].x - recWidth;
        route[i].y = route[i-1].y;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(;i<=16;i++){
        route[i].x = route[i-1].x;
        route[i].y = route[i-1].y - recWidth;
        route[i].color = (route[i-1].color+1)%4;
    }

    route[17].x = route[16].x - recWidth;
    route[17].y = route[16].y - recWidth;
    route[17].color = (route[16].color+1)%4;
    i++;

    for(;i<=20;i++){
        route[i].x = route[i-1].x - recWidth;
        route[i].y = route[i-1].y;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(;i<=26;i++){
        route[i].x = route[i-1].x;
        route[i].y = route[i-1].y - recWidth;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(;i<=29;i++){
        route[i].x = route[i-1].x + recWidth;
        route[i].y = route[i-1].y;
        route[i].color = (route[i-1].color+1)%4;
    }

    route[30].x = route[29].x + recWidth;
    route[30].y = route[29].y - recWidth;
    route[30].color = (route[29].color+1)%4;
    i++;

    for(;i<=33;i++){
        route[i].x = route[i-1].x;
        route[i].y = route[i-1].y - recWidth;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(;i<=39;i++){
        route[i].x = route[i-1].x + recWidth;
        route[i].y = route[i-1].y;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(;i<=42;i++){
        route[i].x = route[i-1].x;
        route[i].y = route[i-1].y + recWidth;
        route[i].color = (route[i-1].color+1)%4;
    }

    route[43].x = route[42].x + recWidth;
    route[43].y = route[42].y + recWidth;
    route[43].color = (route[42].color+1)%4;
    i++;

    for(;i<=46;i++){
        route[i].x = route[i-1].x + recWidth;
        route[i].y = route[i-1].y;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(;i<=51;i++){
        route[i].x = route[i-1].x;
        route[i].y = route[i-1].y + recWidth;
        route[i].color = (route[i-1].color+1)%4;
    }

    for(int a = 0; a < 20; a++){
        airport[i].color = (a/5+1)%4;
        finalroad[i].color = (a/5+1)%4;
    }

    airport[0].x = startPixX + 12 * recWidth;
    airport[0].y = startPixY + 12 * recWidth;
    airport[1].x = startPixX + 13 * recWidth;
    airport[1].y = startPixY + 12 * recWidth;
    airport[2].x = startPixX + 12 * recWidth;
    airport[2].y = startPixY + 13 * recWidth;
    airport[3].x = startPixX + 13 * recWidth;
    airport[3].y = startPixY + 13 * recWidth;
    airport[4].x = startPixX + 14 * recWidth;
    airport[4].y = startPixY + 11 * recWidth;

    airport[5].x = startPixX + 1 * recWidth;
    airport[5].y = startPixY + 12 * recWidth;
    airport[6].x = startPixX + 2 * recWidth;
    airport[6].y = startPixY + 12 * recWidth;
    airport[7].x = startPixX + 1 * recWidth;
    airport[7].y = startPixY + 13 * recWidth;
    airport[8].x = startPixX + 2 * recWidth;
    airport[8].y = startPixY + 13 * recWidth;
    airport[9].x = startPixX + 3 * recWidth;
    airport[9].y = startPixY + 14 * recWidth;

    airport[10].x = startPixX + 1 * recWidth;
    airport[10].y = startPixY + 1 * recWidth;
    airport[11].x = startPixX + 2 * recWidth;
    airport[11].y = startPixY + 1 * recWidth;
    airport[12].x = startPixX + 1 * recWidth;
    airport[12].y = startPixY + 2 * recWidth;
    airport[13].x = startPixX + 2 * recWidth;
    airport[13].y = startPixY + 2 * recWidth;
    airport[14].x = startPixX + 0 * recWidth;
    airport[14].y = startPixY + 3 * recWidth;

    airport[15].x = startPixX + 12 * recWidth;
    airport[15].y = startPixY + 1 * recWidth;
    airport[16].x = startPixX + 13 * recWidth;
    airport[16].y = startPixY + 1 * recWidth;
    airport[17].x = startPixX + 12 * recWidth;
    airport[17].y = startPixY + 2 * recWidth;
    airport[18].x = startPixX + 13 * recWidth;
    airport[18].y = startPixY + 2 * recWidth;
    airport[19].x = startPixX + 11 * recWidth;
    airport[19].y = startPixY + 0 * recWidth;

    finalroad[0].x = startPixX + 13 * recWidth;
    finalroad[0].y = startPixY + 7 * recWidth;
    finalroad[5].x = startPixX + 7 * recWidth;
    finalroad[5].y = startPixY + 13 * recWidth;
    finalroad[10].x = startPixX + 1 * recWidth;
    finalroad[10].y = startPixY + 7 * recWidth;
    finalroad[15].x = startPixX + 7 * recWidth;
    finalroad[15].y = startPixY + 1 * recWidth;

    for(int a = 1; a < 5; a++){
        finalroad[a].x=finalroad[a-1].x-recWidth;
        finalroad[a].y=finalroad[a-1].y;
    }
    for(int a = 6; a < 10; a++){
        finalroad[a].x=finalroad[a-1].x;
        finalroad[a].y=finalroad[a-1].y-recWidth;
    }
    for(int a = 11; a < 15; a++){
        finalroad[a].x=finalroad[a-1].x+recWidth;
        finalroad[a].y=finalroad[a-1].y;
    }
    for(int a = 16; a < 20; a++){
        finalroad[a].x=finalroad[a-1].x;
        finalroad[a].y=finalroad[a-1].y+recWidth;
    }

}

map::~map(){
    delete[] route;
    delete[] airport;
    delete[] finalroad;
};
