#include "socketconnect.h"

socketconnect::socketconnect(QObject* parent)
{
    Q_UNUSED(parent);
//broadcast every 1000ms when not $isConnected
    this->broadcastTimer = new QTimer(this);
    this->broadcastTimer->start(1000);
    connect(this->broadcastTimer, SIGNAL(timeout()), this, SLOT(broadcast()));

    this->broadcastForServer = new QUdpSocket(this);
    broadcastForServer->bind(QHostAddress("192.168.1.112"), 48360, QUdpSocket::DontShareAddress);
    this->receiveCallback = new QUdpSocket();
    this->receiveCallback->bind(48361, QUdpSocket::DontShareAddress);
    connect(this->receiveCallback, &QUdpSocket::readyRead, this, [=](){
        while(this->receiveCallback->hasPendingDatagrams()){
            QByteArray datagram;
            datagram.resize(receiveCallback->pendingDatagramSize());
            this->receiveCallback->readDatagram(datagram.data(),datagram.size(), &hostOfServer, &portOfServer);
            qDebug()<<"client received callback:"<<hostOfServer.toString()<<":"<<datagram.data();
        }});
//create a tcp socket and connect connecting signals
    this->gameSocket = new QTcpSocket(this);
    connect(this->gameSocket, &QTcpSocket::connected, this, [&](){isConnected=true;qDebug()<<"connected";});
    connect(this->gameSocket, &QTcpSocket::disconnected, this, [=](){isConnected=false;qDebug()<<"disconnected";});
}

socketconnect::~socketconnect(){
    //release the tcp connect and delete udp tcp sockets
    delete broadcastForServer;
    delete receiveCallback;
    delete gameSocket;
}
//tcp connect to host
int socketconnect::connectToServer(){
    gameSocket->connectToHost(hostOfServer, 48362, QTcpSocket::ReadWrite);
    return 0;
}
//udp broadcast
void socketconnect::broadcast(){
    if(!this->isConnected || 1){
        qDebug()<<"213";
        this->broadcastForServer->writeDatagram(QString("who are fc server").toLatin1(),
                                            QString("who are fc server").length(), QHostAddress::Broadcast, 48360);
    }
}
