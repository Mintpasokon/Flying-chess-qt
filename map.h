#ifndef map_H
#define map_H
#include <QDebug>

const int startPixX = 200;
const int startPixY = 50;
const int recWidth = 40;

struct rectangle{
    int x;
    int y;
    int color;//clockwise 0,1(me),2,3 and 4=nothing
};

class map
{
    friend class MainWindow;
public:
    map();
    ~map();

    struct rectangle* route,* airport,* finalroad;//this is the coordinate of every rectangle in the map
};

#endif // map_H
