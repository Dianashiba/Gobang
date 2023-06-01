#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class myButton : public QPushButton
{
    Q_OBJECT
public:
    myButton(QString image);

    //图片地址
    QString img;

    //弹跳特效
    void zoomUp();
    void zoomDown();

signals:

};

#endif // MYBUTTON_H
