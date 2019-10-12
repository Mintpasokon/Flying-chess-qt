#include "socketserver.h"

socketserver::socketserver()
{
    //liston broadcast by port 48360 and respond to 48361
    udpRecivieBroadcast = new QUdpSocket();
    udpCallback = new QUdpSocket();
    udpRecivieBroadcast->bind(48360, QUdpSocket::DontShareAddress);
    connect(udpRecivieBroadcast, &QUdpSocket::readyRead, this, [=](){
        while (udpRecivieBroadcast->hasPendingDatagrams()) {
            //send a udp frame to the client
            QByteArray datagram;
            QString content = "i am fc server";
            datagram.resize(udpRecivieBroadcast->pendingDatagramSize());
            udpRecivieBroadcast->readDatagram(datagram.data(),datagram.size(), &hostOfClient,&portOfClient);
            if(this->active){
                udpCallback->writeDatagram(content.toLatin1(), content.length(), hostOfClient, 48361);
                qDebug()<<"server received broadcast:"<<hostOfClient.toString()<<":"<<datagram.data();}
        }
    });

    //server thread
    gameServer = new QTcpServer();
    connect(gameServer, &QTcpServer::newConnection, this, &socketserver::newConnect);
    gameServer->listen(QHostAddress::Any, 48362);
}
//trigger at new connection, add new socket to the quene
void socketserver::newConnect(){
    playerNum++;
    qDebug()<<"New connection, now "+QString::number(playerNum)+" players connected";
}

socketserver::~socketserver(){
    delete udpCallback;
    delete udpRecivieBroadcast;
    delete gameServer;
}
