#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include "mybutton.h"
#include <QTimer>
#include <QDebug>
#include <Qimage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置固定大小
    setFixedSize(1200,740);
    //设置图标
    setWindowIcon(QIcon(":/images/ico.jpg"));
    //设置场景标题
    setWindowTitle("五子棋游戏");

    //设置按钮 分别代表pvp，pve，online模式
    myButton * eve = new myButton(":/images/ComAndCom.png");
    eve->setParent(this);
    eve->move(this->width()*0.50-eve->width()*0.5,this->height()*0.7);

    myButton * pvp = new myButton(":/images/PeoPleTogether.png");
    pvp->setParent(this);
    pvp->move(this->width()*0.5-pvp->width()*0.5,this->height()*0.5);

    myButton * pve = new myButton(":/images/PeopleAndComputer.png");
    pve->setParent(this);
    pve->move(this->width()*0.5-pve->width()*0.5,this->height()*0.3);

    myButton * ponline = new myButton(":/images/Online.png");
    ponline->setParent(this);
    ponline->move(this->width()*0.5-ponline->width()*0.5,this->height()*0.1);

    //创建游戏对象
    playpvp=new pvpScene();
    playpve=new pveScene();
    playponline=new login();
    playeve=new eveScene();


    //监听返回信号
    connect(playpvp,&pvpScene::back,[=](){
        playpvp->hide();
        this->show();
    });

    connect(playpve,&pveScene::back,[=](){
        playpve->hide();
        this->show();
    });

    connect(playponline,&login::back,[=](){
        playponline->hide();
        this->show();
    });

    connect(playeve,&eveScene::back,[=](){
        playeve->hide();
        this->show();
    });

    //监听按钮按下操作
    connect(pvp,&QPushButton::clicked,[=](){

        //做弹起特效
        pvp->zoomDown();
        pvp->zoomUp();

        QTimer::singleShot(400,this,[=](){
            //进入pvp场景
            this->hide();
            playpvp->constructor();
            playpvp->show();

        });

    });

    connect(pve,&QPushButton::clicked,[=](){

        //做弹起特效
        pve->zoomDown();
        pve->zoomUp();

        QTimer::singleShot(400,this,[=](){
            //进入pve场景
            this->hide();
            playpve->constructor();
            playpve->show();

        });

    });

    connect(ponline,&QPushButton::clicked,[=](){

        //做弹起特效
        ponline->zoomDown();
        ponline->zoomUp();

        QTimer::singleShot(400,this,[=](){
            //进入在线pvp场景
            this->hide();
            playponline->loginupdate();
            playponline->show();

        });

    });
    connect(eve,&QPushButton::clicked,[=](){

        //做弹起特效
        eve->zoomDown();
        eve->zoomUp();

        QTimer::singleShot(400,this,[=](){
            //进入eve场景
            this->hide();
            playeve->constructor();
            playeve->show();

        });

    });

}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);

    //画背景图
    QPixmap pix;
    painter.drawPixmap(rect(),QPixmap(":/images/jwf2.png"),QRect());

}

MainWindow::~MainWindow()
{
    delete ui;
}


