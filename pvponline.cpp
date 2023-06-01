#include "pvponline.h"
#include <QTimer>
#include <QMessageBox>

pvponline::pvponline(online * o,QString mac)
{
    this->o=o;
    this->mac=mac;


    whiteBtn->setParent(this);
    whiteBtn->move(100,340);
    whiteBtn->show();

    blackBtn->setParent(this);
    blackBtn->move(100,500);
    blackBtn->show();

    fallBtn->setParent(this);
    fallBtn->setGeometry(QRect(320, 915, 121, 121));
    fallBtn->hide();

    //链接按钮
    connect(whiteBtn,&QPushButton::clicked,[=](){
        whiteBtn->zoomDown();
        whiteBtn->zoomUp();
        QTimer::singleShot(400,this,[=](){
            bool ret=chooseflag(2);
            if(ret){
                blackBtn->hide();
                fallBtn->show();
                colorFlag=2;
                int b=o->chessupdate();
                if(b==3){
                    beginFlag=0;
                    wait();
                }else{
                    beginFlag=1;
                    myFlag=false;
                    onlineupdate();
                }
                whiteBtn->hide();
            }else{
                QMessageBox::warning(this,"","该位置已经被占用");
            }

        });
    });
    connect(blackBtn,&QPushButton::clicked,[=](){
        blackBtn->zoomDown();
        blackBtn->zoomUp();
        QTimer::singleShot(400,this,[=](){
            bool ret=chooseflag(1);
            if(ret){
                whiteBtn->hide();
                fallBtn->show();
                colorFlag=1;
                int b=o->chessupdate();
                qDebug()<<b;
                if(b==3){
                    beginFlag=0;
                    wait();
                }else{
                    beginFlag=1;
                    myFlag=true;
                }
                blackBtn->hide();
            }else{
                QMessageBox::warning(this,"","该位置已经被占用");
            }
        });
    });
    connect(fallBtn,&QPushButton::clicked,[=](){
        fallBtn->zoomDown();
        fallBtn->zoomUp();
        QTimer::singleShot(400,this,[=](){
            exit();
        });
    });
}


void pvponline::end(){
    int ret =0;
    //弹出胜负结果会话框
    if(winFlag==3-colorFlag){
        ret = QMessageBox::information(this,
                                       "你失败了",
                                       "太遗憾了！\n再来一局？",
                                       QMessageBox::Yes|QMessageBox::No,
                                       QMessageBox::Yes);
    }
    else if(winFlag==colorFlag){
        ret = QMessageBox::information(this,
                                       "您获胜了",
                                       "恭喜您获胜！\n再来一局？",
                                       QMessageBox::Yes|QMessageBox::No,
                                       QMessageBox::Yes);
    }else{
        ret = QMessageBox::information(this,
                                       "平局",
                                       "平局了！\n再来一局？",
                                       QMessageBox::Yes|QMessageBox::No,
                                       QMessageBox::Yes);
    }

    //根据玩家判断做出选项
    if(ret==QMessageBox::Yes)
    {
        o->exit(mac);
        constructor();
        update();
    }
    else if(ret==QMessageBox::No)
    {
        o->exit(mac);
        constructor();
        emit this->back();
    }
}

//当对手未进入棋局时
void pvponline::wait(){
    waiting=true;
    connect(this,&pvponline::back,[&](){
        waiting=false;
    });
    QTimer::singleShot(1000,this,[&](){
        int ret=o->chessupdate();

        if(ret==3&&waiting){
            return wait();
        }else{
            if(waiting){
                beginFlag=1;
                if(colorFlag==1){
                    myFlag=true;
                }else{
                    onlineupdate();
                }
            }
        }
    });
}

//对局等待对方下子时
void pvponline::onlineupdate(){
    waiting=true;
    connect(this,&pvponline::back,[&](){
        waiting=false;
    });
    QTimer::singleShot(1000,this,[&](){
        int ret=o->chessupdate();

        if(ret==0&&waiting){
            return onlineupdate();
        }else{
            if(ret==3&&waiting){
                QMessageBox::warning(this,"","对方已离开");
                constructor();
                emit this->back();
                return;
            }
            if(waiting){
                myFlag=true;
                for(int i=0;i<30;i++){
                    for(int j=0;j<30;j++){
                        if(chess[i][j]!=o->chess[i][j]){
                            chessX=i;
                            chessY=j;
                            chess[i][j]=o->chess[i][j];
                        }
                    }
                }
                //判断是否结束
                bool ifisend=this->isend();
                update();
                //如果已经结束进行结束操作
                if(ifisend){
                    end();
                }else{
                    onlineupdate();
                }
            }
        }
    });


}

//投降或退出时
void pvponline::exit(){
        constructor();
        bool ret=o->exit(mac);
        if(!ret){
            int b=o->chessupdate();
            if(b!=3)return exit();
        }
        emit this->back();
}

//进入对局选择阵营时
bool pvponline::chooseflag(int flag){
    bool ret=o->wait(mac,flag);
    return ret;
}

//结束时清理棋盘，初始化
void pvponline::constructor(){
    beginFlag=0;
    colorFlag=0;
    myFlag=false;
    waiting=true;

    //清空棋盘
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            chess[i][j]=0;
            o->chess[i][j]=0;
        }
    }

    //初始化各模块
    whiteBtn->show();
    blackBtn->show();
    fallBtn->hide();
    update();
}

//判定鼠标按下位置
void pvponline::mouseReleaseEvent(QMouseEvent *event){
    //判定是否开始以及鼠标位置是否正确
    if((!beginFlag)||(!myFlag)) return;
    int x=event->x(),y=event->y();
    if(x<210||x>1100||y<40||y>930) return;

    chessX=(x-216+14)/30;chessY=(y-46+14)/30;

    //判断点击处是否有棋子，若有棋子则返回
    if(chess[chessX][chessY]!=0) return;

    myFlag=false;
    //下棋子
    chess[chessX][chessY]=colorFlag;
    //更新online棋盘
    o->chess[chessX][chessY]=colorFlag;
    //更新服务器棋盘
    o->up(mac,colorFlag,chessX,chessY);

    //判断是否结束
    bool ifisend=this->isend();
    update();
    //如果已经结束进行结束操作
    if(ifisend){
        end();
    }else{
        onlineupdate();
    }
}

void pvponline::closeEvent(QCloseEvent *event){
    this->exit();
    event->ignore();
}
