#ifndef PVESCENE_H
#define PVESCENE_H

#include "BaseScene.h"
#include "mybutton.h"
#include <Qlabel>

class pveScene : public baseScene
{
    Q_OBJECT
public:
    pveScene();

    int aiFlag=0;
    QLabel * label;

    myButton * peopleFirstBtn=new myButton(":/images/PlayerFirst.png");
    myButton * computerFirstBtn=new myButton(":/images/ComputerFirst.png");
    myButton * againBtn=new myButton(":/images/AgainBegin.png");


    void end();

    void ai();

    int chessType(int rotate, int i, int j);

    int value(int i, int j);

    void moveByOne(int rotate, int *i, int *j);



    //重写鼠标释放函数
    void mouseReleaseEvent(QMouseEvent *event);

    //重新开始的函数
    void constructor();

signals:

};

#endif // PVESCENE_H
