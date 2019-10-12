#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    this->planes = new plane*[16];

    this->messageLabel = new QLabel(this);

    this->maps = new map();
    //connect to server through soc
    this->soc = new socketconnect();

    //be a server through ser
    this->ser = new socketserver();

    //buttons
    this->startButton = new QPushButton(this);
    this->diceButton = new QPushButton(this);
    this->connectButton = new QPushButton(this);
    this->diceButton->setGeometry(startPixX + 16 * recWidth - 200, startPixY + 14 * recWidth, 300, 50);
    this->diceButton->setText("dice");
    connect(this->diceButton, &QPushButton::clicked, this->diceButton, [=](){this->diceButton->setText(this->soc->hostOfServer.toString());});
    this->startButton->setGeometry(900, 300, 60, 30);
    this->startButton->setText("start");
    this->connectButton->setGeometry(900, 260, 90, 40);
    this->connectButton->setText("connect");
    //the $isServer checkbox
    this->isServer = new QCheckBox(this);
    this->isServer->setGeometry(900,200,20,20);
    this->isServerLabel = new QLabel(this);
    this->isServerLabel->setGeometry(915,195,60,25);
    this->isServerLabel->setText("server");
    connect(this->isServer, &QCheckBox::stateChanged, this, &MainWindow::isServerChanged);
    //init planes
    for(int i = 0; i < 16; i++){
        this->planes[i] = new plane(this,i);
        this->planes[i]->setGeometry(this->maps->airport[i+i/4].x,this->maps->airport[i+i/4].y,recWidth,recWidth);
    }
    //when plane clicked
    for(int i = 0; i < 16; i++)
        connect(this->planes[i], &plane::send, this, &MainWindow::planeClicked);
    //when press $connect button
    connect(this->connectButton, &QPushButton::clicked, this, &MainWindow::on_connectButton_clicked);

}

MainWindow::~MainWindow()
{
    //delete ui;
    for(int i = 0; i < 16; i++){
        delete planes[i];
    }
    delete[] planes;
    delete maps;
    delete soc;
    delete ser;
    delete messageLabel;
    delete isServer;
    delete isServerLabel;
    delete startButton;
    delete connectButton;
    delete diceButton;

}

void MainWindow::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);
    QPainter painter(this);
    QPixmap pix[4];
    pix[0].load("yellow.png");
    pix[1].load("blue.png");
    pix[2].load("green.png");
    pix[3].load("red.png");

    QPixmap pixPlane[4];
    pixPlane[0].load("yellowplane.png");
    pixPlane[1].load("blueplane.png");
    pixPlane[2].load("greenplane.png");
    pixPlane[3].load("redplane.png");

    for(int i = 0; i < 52; i++){
       painter.drawPixmap(this->maps->route[i].x,this->maps->route[i].y,recWidth,recWidth,pix[(i+color+3)%4]);
    }
    for(int i = 0; i < 20; i++){
       painter.drawPixmap(this->maps->finalroad[i].x,this->maps->finalroad[i].y,recWidth,recWidth,pix[(i/5+color)%4]);
       painter.drawPixmap(this->maps->airport[i].x,this->maps->airport[i].y,recWidth,recWidth,pix[(i/5+color)%4]);
    }
    for(int i = 0; i < 16; i++){
       painter.drawPixmap(this->planes[i]->x(),this->planes[i]->y(),recWidth,recWidth,pixPlane[(i/4+color)%4]);
    }

}

void MainWindow::planeClicked(int number){
    this->deg(number);
    if(status == 2 && number <= 3){
        this->movePlaneBy(number,diceNumber);
        //status = 0;
    }
}

void MainWindow::movePlaneBy(int Plane, int steps){

    if(this->planes[Plane]->region == 0 && steps >= 5){
        this->planes[Plane]->move(this->maps->airport[(Plane/4+1)*5-1].x, this->maps->airport[(Plane/4+1)*5-1].y);
        this->planes[Plane]->region = ready;
        //tell the server
    }else if(this->planes[Plane]->region == 1){
        for(int i = 1;i <= steps; i++)
            this->planes[Plane]->move(this->maps->route[i].x,this->maps->route[i].y);
        this->planes[Plane]->locationNum += steps;
        this->planes[Plane]->region = route;
    }else if(this->planes[Plane]->region == 2){
        for(int i = this->planes[Plane]->locationNum;i <= this->planes[Plane]->locationNum + steps; i++)
            this->planes[Plane]->move(this->maps->route[i].x,this->maps->route[i].y);
        this->planes[Plane]->locationNum += steps;
    };

    //if the plane moves, tell server
}

void MainWindow::on_connectButton_clicked(){
    this->connectButton->setText("connecting");
    this->soc->connectToServer();

}
//when this computer is server, hide the connect button
void MainWindow::isServerChanged(){
    qDebug()<<"isServer state:"<<this->isServer->isChecked();
    if(!this->isServer->isChecked()){
        //this->connectButton->show();
        this->ser->setActive(false);
        this->soc->active = true;
    }
    else{
        //this->connectButton->hide();
        this->ser->setActive(true);
        this->soc->active = false;
    }
}
