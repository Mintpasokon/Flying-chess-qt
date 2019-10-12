#ifndef SOCKETCONNECT_H
#define SOCKETCONNECT_H

#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkAddressEntry>
#include <QThread>
#include <QTextBrowser>
#include <QString>
#include <QTextEdit>
#include <QTimer>
#include <QDebug>

class socketconnect : public QObject
{
    Q_OBJECT
    friend class MainWindow;
public:
    socketconnect(QObject *parent = 0);
    ~socketconnect();
    bool isConnectedToServer = 0;
    QHostAddress hostOfServer;
    quint16 portOfServer;
    bool active = true;
    bool isConnected = false;

signals:
    void connected();
    void messageFromServer();
    void dicenumber(int dicenum);
    void planeMove(int plane, int steps);

public slots:
    int connectToServer();
    void clickDice(){}
    void clickPlane(){}
    void broadcast();


private:

    QUdpSocket* broadcastForServer, *receiveCallback;
    QTcpSocket* gameSocket;
    QTimer* broadcastTimer;
    QNetworkAddressEntry localIp;
};


#endif // SOCKETCONNECT_H
