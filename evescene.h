#ifndef EVESCENE_H
#define EVESCENE_H

#include "BaseScene.h"
#include "mybutton.h"
#include <Qlabel>

class eveScene : public baseScene
{
    Q_OBJECT
public:
    eveScene();

    int aiFlag=1;

    myButton * againBtn=new myButton(":/images/AgainBegin.png");
    myButton * aiToAi=new myButton(":/images/BeginGame.png"); //这个按钮用于ai对ai的模式

    void end();

    void ai();

    int chessType(int rotate, int i, int j);

    int value(int i, int j);

    void moveByOne(int rotate, int *i, int *j);

    void aitoai();

    //重写鼠标释放函数
    void mousePressEvent(QMouseEvent *event);

    //重新开始的函数
    void constructor();

signals:

};

#endif // PVESCENE_H
