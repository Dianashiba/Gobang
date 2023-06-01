#ifndef PVPONLINE_H
#define PVPONLINE_H

#include "BaseScene.h"
#include "online.h"
#include <QLabel>


class pvponline :  public baseScene
{
    Q_OBJECT
public:
    pvponline(online * o,QString mac);
    QString mac;
    online * o;


    bool myFlag=false;

    myButton * whiteBtn=new myButton(":/images/BWhite.png");
    myButton * blackBtn=new myButton(":/images/BBlack.png");
    myButton * fallBtn=new myButton(":/images/Fall.png");

    void end();
    void wait();
    void onlineupdate();
    void exit();



    bool chooseflag(int flag);
    void constructor();


    //重写鼠标释放函数
    void mouseReleaseEvent(QMouseEvent *event);
    //重写关闭窗口函数
    void closeEvent(QCloseEvent *event);

private:
    bool waiting=true;

signals:
    void back();
};

#endif // PVPONLINE_H
