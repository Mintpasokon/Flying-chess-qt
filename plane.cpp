#include "plane.h"

plane::plane(QWidget *parent, int Number) :
    QLabel(parent)
{
    number = Number;
    airportNum = number%4;
    locationNum = 0;
}

void plane::mousePressEvent(QMouseEvent *ev){
    Q_UNUSED(ev);
    emit send(this->number);
}
