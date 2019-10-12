#ifndef PLANE_H
#define PLANE_H
#include <QLabel>
#include <QMouseEvent>

enum colors{y,b,g,r};
enum regions{airport, ready, route, finalroad, arrived};

class plane : public QLabel
{
    Q_OBJECT
    friend class MainWindow;
public:
    plane(QWidget *parent, int);
protected:
    void mousePressEvent(QMouseEvent *ev);
signals:
    void send(int);
private:
    int number;
    int airportNum;//fixed 0,1,2,3
    regions region = airport ;//0:airport, 1:ready, 2:route, 3:finalRoad, 4:arrived
    int locationNum;
    colors color;
};

#endif // PLANE_H
