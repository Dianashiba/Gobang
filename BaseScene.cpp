#include "BaseScene.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>


baseScene::baseScene(QWidget *parent)
    : QWidget{parent}
{
    //设置固定大小
    setFixedSize(1100,1050);
    //设置图标
    setWindowIcon(QIcon(":/images/ico.jpg"));
    //设置场景标题
    setWindowTitle("五子棋游戏");
}





void baseScene::paintEvent(QPaintEvent *event){
    //画背景
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0,1200,1200),QPixmap(":/images/980.png"));
//    painter.drawPixmap(QRect(0,0,1200,740),QPixmap(":/images/qipan.png"));


    // 画棋盘格子
    int gridSize = 30; // 格子大小
    int startX = 216;  // 棋盘起始X坐标
    int startY = 46;   // 棋盘起始Y坐标 46

    //绘制水平线
    for (int i = 0; i < 30; ++i) {
        painter.drawLine(startX, startY + i * gridSize, startX + 29 * gridSize, startY + i * gridSize);
    }

    // 绘制垂直线
    for (int i = 0; i < 30; ++i) {
        painter.drawLine(startX + i * gridSize, startY, startX + i * gridSize, startY + 29 * gridSize);
    }
    //画棋子
    for(int i=0;i<30;++i)
        for(int j=0;j<30;++j)
        {
            if(chess[i][j]==1)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/BBlack.png"));
            if(chess[i][j]==2)
                painter.drawPixmap(QRect(202+i*30,32+j*30,28,28),QPixmap(":/images/BWhite.png"));
        }

    //如果游戏开始了，那么绘制棋子的提示
    if(beginFlag){
        //画上次下棋子的位置 用红色标记
        painter.setBrush(Qt::red);
        painter.drawEllipse(QRect(chessX*30+212,chessY*30+42,8,8));
    }
}


bool baseScene::isend(){
    //判断黑子取胜
    for(int i=0;i<30;i++){
        if(winFlag)break;
        for(int j=0;j<26;j++){
            if(chess[i][j]==1&&chess[i][j+1]==1&&chess[i][j+2]==1&&chess[i][j+3]==1&&chess[i][j+4]==1){
                winFlag=1;
                break;
            }
        }

    }
    for(int i=0;i<26;i++){
        if(winFlag)break;
        for(int j=0;j<30;j++){
            if(chess[i][j]==1&&chess[i+1][j]==1&&chess[i+2][j]==1&&chess[i+3][j]==1&&chess[i+4][j]==1){
                winFlag=1;
                break;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(winFlag)break;
        for(int j=0;j<26;j++){
            if(chess[i][j]==1&&chess[i+1][j+1]==1&&chess[i+2][j+2]==1&&chess[i+3][j+3]==1&&chess[i+4][j+4]==1){
                winFlag=1;
                break;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(winFlag)break;
        for(int j=0;j+i<55;j++){
            if(j-4<0)continue;
            if(chess[i][j]==1&&chess[i+1][j-1]==1&&chess[i+2][j-2]==1&&chess[i+3][j-3]==1&&chess[i+4][j-4]==1){
                winFlag=1;
                break;
            }
        }
    }
    //判断白子取胜
    for(int i=0;i<30;i++){
        if(winFlag)break;
        for(int j=0;j<26;j++){
            if(chess[i][j]==2&&chess[i][j+1]==2&&chess[i][j+2]==2&&chess[i][j+3]==2&&chess[i][j+4]==2){
                winFlag=2;
                break;
            }
        }

    }
    for(int i=0;i<26;i++){
        if(winFlag)break;
        for(int j=0;j<30;j++){
            if(chess[i][j]==2&&chess[i+1][j]==2&&chess[i+2][j]==2&&chess[i+3][j]==2&&chess[i+4][j]==2){
                winFlag=2;
                break;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(winFlag)break;
        for(int j=0;j<26;j++){
            if(chess[i][j]==2&&chess[i+1][j+1]==2&&chess[i+2][j+2]==2&&chess[i+3][j+3]==2&&chess[i+4][j+4]==2){
                winFlag=2;
                break;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(winFlag)break;
        for(int j=0;j+i<55;j++){
            if(j-4<0)continue;
            if(chess[i][j]==2&&chess[i+1][j-1]==2&&chess[i+2][j-2]==2&&chess[i+3][j-3]==2&&chess[i+4][j-4]==2){
                winFlag=2;
                break;
            }
        }
    }
    if(winFlag)return 1;
    //判断平局
    bool ping =1;
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            if(!chess[i][j])ping =0;
        }
    }
    if(ping){
        winFlag=3;
        return 1;
    }
    return 0;
}


//当点击右上方关闭窗口时进行阻拦，返回主窗口并隐藏游戏界面
void baseScene::closeEvent(QCloseEvent *event){
    emit this->back();
    this->hide();
    event->ignore();
}
