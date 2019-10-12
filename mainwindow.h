#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTextEdit>
#include <QTextBrowser>
#include <QThread>
#include <QCheckBox>
#include "map.h"
#include "plane.h"
#include "socketconnect.h"
#include "socketserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class map;
    friend class socketconnect;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void deg(int number){qDebug()<<number;}
    void movePlaneBy(int plane, int dest);
    void on_connectButton_clicked();

    int diceNumber = 5;
    int color = 1;//0:yellow, 1:blue, 2:green, 3:red
    int status = 2;//0:not ready, 1:ready to dice, 2:having diced

public slots:
    void isServerChanged();

protected:
    void paintEvent(QPaintEvent*);
    void planeClicked(int);

private slots:

private:
    //Ui::MainWindow *ui;

    plane** planes;
    map *maps;
    socketconnect *soc;
    socketserver *ser;

    QLabel* messageLabel;
    QCheckBox* isServer;
    QLabel* isServerLabel;

    QPushButton* startButton, *diceButton, *connectButton;
};

#endif // MAINWINDOW_H
