#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "online.h"
#include <QCloseEvent>
#include "pvponline.h"
#include <QTimer>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    online * o;
    QString mac;
    bool registed=false;
    QString userName="未注册";

    pvponline * pvponlinescene;

    void loginupdate();
    void unregist();
    void rename();
    void regist();
    void registrandom();
    void closeEvent(QCloseEvent *event);

private:
    Ui::login *ui;
    QString getMac();
signals:
    //返回信号
    void back();
};

#endif // LOGIN_H
