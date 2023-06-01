#include "login.h"
#include "ui_login.h"
#include <QSysInfo>
#include <QMessageBox>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    //设置ui
    ui->setupUi(this);
    //设置图标
    setWindowIcon(QIcon(":/images/ico.jpg"));
    //设置场景标题
    setWindowTitle("五子棋游戏");

    //更新联网和windows序列号
    o=new online();
    mac=getMac();
    qDebug()<<mac;

    pvponlinescene=new pvponline(o,mac);
    //监听返回信号
    connect(pvponlinescene,&pvponline::back,[=](){
        pvponlinescene->hide();
        qDebug()<<1;
        this->show();
    });
    //监听开始按钮
    connect(ui->start,&QPushButton::clicked,[=](){
        if(registed){
            //进入下一个场景
            this->hide();
            pvponlinescene->constructor();
            pvponlinescene->show();
        }else{
            unregist();
        }
    });
    //监听重命名按钮
    connect(ui->rename,&QPushButton::clicked,[=](){
        if(registed){
            rename();
        }else {
            unregist();
        }
    });
    //监听注册按钮
    connect(ui->regist,&QPushButton::clicked,[=](){
        if(registed){
            int ret = QMessageBox::information(this,
                                               "已注册",
                                               "已经注册了，是否直接开始？",
                                               "yes",
                                               "no",
                                               "",
                                               0,
                                               1);
            //根据玩家判断做出选项
            if(ret==0)
            {
                ui->start->click();
            }
            else if(ret==1)
            {
                emit this->back();
                this->hide();
            }
        }else {
            regist();
        }
    });
    //监听随机注册按钮
    connect(ui->registrandom,&QPushButton::clicked,[=](){
        if(registed){
            int ret = QMessageBox::information(this,
                                               "已注册",
                                               "已经注册了，是否直接开始？",
                                               "yes",
                                               "no",
                                               "",
                                               0,
                                               1);
            //根据玩家判断做出选项
            if(ret==0)
            {
                ui->start->click();
            }
            else if(ret==1)
            {
                emit this->back();
                this->hide();
            }
        }else {
            registrandom();
        }
    });
}

//注册
void login::regist(){
    QString name=ui->edit->text();
    if(name==""){
        QMessageBox::warning(this,"","请输入名字");
    }else{
        bool ret=o->regist(mac,name);
        if(!ret){
            qDebug()<<"error";
        }else{
            qDebug()<<ret;
            loginupdate();
        }
    }
}

//随机用户名注册
void login::registrandom(){
    bool ret=o->regist(mac);
    if(!ret){
        qDebug()<<"error";
    }else{
        qDebug()<<ret;
        loginupdate();
    }

}

//重命名
void login::rename(){
    QString name=ui->edit->text();
    bool ret=o->rename(mac,name);
    qDebug()<<ret;
    loginupdate();
}

void login::loginupdate(){
    registed=o->isfound(mac);
    if(registed){
        ui->userisfound->setText("已注册");
        userName=o->find(mac);
        ui->username->setText(userName);
    }else{
        ui->userisfound->setText("未注册");
    }
}

QString login::getMac(){
    // 获取当前系统的序列号
    QString computerName = QSysInfo::machineUniqueId();
    qDebug() << "Computer Name:" << computerName;
    return computerName;
}

void login::closeEvent(QCloseEvent *event){
    emit this->back();
    this->hide();
    event->ignore();
}

void login::unregist(){
    int ret = QMessageBox::information(this,
                                       "未注册",
                                       "你还没有注册哦",
                                       "这就去注册",
                                       "超！不玩了",
                                       "",
                                       0,
                                       1);
    //根据玩家判断做出选项
    if(ret==0)
    {
        update();
    }
    else if(ret==1)
    {
        emit this->back();
        this->hide();
    }
}

login::~login()
{
    delete ui;
}
