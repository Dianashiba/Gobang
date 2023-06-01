#include "pvpscene.h"
#include <QStyle>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QFont>

pvpScene::pvpScene()
{
    //设置开始按钮
    startBtn->setParent(this);
    startBtn->setGeometry(QRect(30, 750, 121, 121));
    //设置重新开始按钮
    againBtn->setParent(this);
    againBtn->setGeometry(QRect(30, 750, 121, 121));
    againBtn->hide();

    //链接开始按钮
    connect(startBtn,&QPushButton::clicked,[=](){
        startBtn->zoomDown();
        startBtn->zoomUp();
        QTimer::singleShot(400,this,[=](){
            startBtn->hide();
            againBtn->show();
            beginFlag=1;
        });
    });
    connect(againBtn,&QPushButton::clicked,[=](){
        againBtn->zoomDown();
        againBtn->zoomUp();
        QTimer::singleShot(400,this,[=](){

            constructor();

        });
    });

}

//判定鼠标按下位置
void pvpScene::mouseReleaseEvent(QMouseEvent *event){
    //判定是否开始以及鼠标位置是否正确
    if(!beginFlag) return;
    int x=event->x(),y=event->y();
    if(x<210||x>1100||y<40||y>930) return;

    chessX=(x-216+14)/30;chessY=(y-46+14)/30;
    //判断点击处是否有棋子，若有棋子则返回
    if(chess[chessX][chessY]!=0) return;

    //下棋子
    chess[chessX][chessY]=colorFlag;
    colorFlag=3 - colorFlag;

    //判断是否结束
    bool ifisend=this->isend();
    //如果已经结束进行结束操作
    if(ifisend){
        end();
    }

    update();
}

void pvpScene::end(){
    int ret =0;
    //弹出胜负结果会话框
    if(winFlag==2){
        ret = QMessageBox::information(this,
                                       "白棋获胜",
                                       "恭喜白棋获胜！\n再来一局？",
                                       QMessageBox::Yes|QMessageBox::No,
                                       QMessageBox::Yes);
    }
    else if(winFlag==1){
        ret = QMessageBox::information(this,
                                       "黑棋获胜",
                                       "恭喜黑棋获胜！\n再来一局？",
                                       QMessageBox::Yes|QMessageBox::No,
                                       QMessageBox::Yes);
    }else if(winFlag==3){
        ret = QMessageBox::information(this,
                                       "平局",
                                       "平局了！\n再来一局？",
                                       QMessageBox::Yes|QMessageBox::No,
                                       QMessageBox::Yes);
    }else{

    }

    //根据玩家判断做出选项
    if(ret==QMessageBox::Yes)
    {
        update();
        constructor();
    }
    else if(ret==QMessageBox::No)
    {
        emit this->back();
        this->hide();
    }
}

//初始化函数
void pvpScene::constructor(){
    //清空棋盘
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            chess[i][j]=0;
        }
    }
    //初始化各模块
    againBtn->hide();
    startBtn->show();
    beginFlag=0;
    winFlag=0;
    colorFlag=1;

    update();
}

