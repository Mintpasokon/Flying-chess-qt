#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QUdpSocket>
#include <QDebug>

class socketserver : public QObject
{
    Q_OBJECT
    friend class MainWindow;
public:
    socketserver();
    ~socketserver();
    void setActive(bool a){active = a;}

public slots:
    void newConnect();


private:
    bool active = false;
    QUdpSocket* udpRecivieBroadcast, *udpCallback;
    QTcpServer* gameServer;
    QHostAddress hostOfClient;
    quint16 portOfClient;
    int playerNum = 1;

};

#endif // SOCKETSERVER_H
