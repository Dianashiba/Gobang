#ifndef BASESCENE_H
#define BASESCENE_H

#include <QWidget>
#include <QCloseEvent>
#include "mybutton.h"

class baseScene : public QWidget
{
    Q_OBJECT
public:
    explicit baseScene(QWidget *parent = nullptr);

    //判断是否结束
    bool isend();

    //绘制背景函数
    void paintEvent(QPaintEvent *event);


    //棋盘上每个点的值，0无子，1黑子，2白子
    int chess[30][30]={};
    //棋盘坐标
    int chessX=0,chessY=0;
    //当前颜色标志,输赢状态标志,是否开始标志，
    int colorFlag=1;
    int winFlag=0, beginFlag=0;

    //重写关闭窗口函数
    void closeEvent(QCloseEvent *event);

signals:
    void back();
};

#endif // BASESCENE_H
