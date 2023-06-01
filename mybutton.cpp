#include "mybutton.h"
#include <QPixmap>
#include<QPropertyAnimation>

myButton::myButton(QString image){
    //存储图片路径
    QString img=image;

    QPixmap pix;
    bool ret = pix.load(img);
    if(!ret)
    {
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片
    this->setStyleSheet("QPushButton{border:0px}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void myButton::zoomUp(){
    //创建动画对象 及 动画时间
    QPropertyAnimation * ani=new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);

    ani->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置曲线
    ani->setEasingCurve(QEasingCurve::OutBounce);

    ani->start();
}
void myButton::zoomDown(){
    //创建动画对象 及 动画时间
    QPropertyAnimation * ani=new QPropertyAnimation(this,"geometry");
    ani->setDuration(200);

    ani->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    ani->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置曲线
    ani->setEasingCurve(QEasingCurve::OutBounce);

    ani->start();
}
