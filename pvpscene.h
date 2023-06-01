#ifndef PVPSCENE_H
#define PVPSCENE_H

#include "BaseScene.h"
#include <QLabel>

class pvpScene : public baseScene
{
    Q_OBJECT
public:
    pvpScene();

    myButton * startBtn=new myButton(":/images/BeginGame.png");
    myButton * againBtn=new myButton(":/images/AgainBegin.png");


    QLabel * label;
    void end();

    //重写鼠标释放函数
    void mouseReleaseEvent(QMouseEvent *event);

    //重新开始的函数
    void constructor();


signals:

};

#endif // PVPSCENE_H
