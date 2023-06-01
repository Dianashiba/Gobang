#ifndef ONLINE_H
#define ONLINE_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QEventLoop>
#include <QString>

class online : public QObject
{
    Q_OBJECT
public:

    int chess[30][30]={};

    online(QObject *parent = nullptr);

    int chessupdate();
    bool wait(QString mac,int color);
    bool up(QString mac,int color,int h,int l);
    bool exit(QString mac);
    bool isfound(QString mac);
    QString find(QString mac);
    bool regist(QString mac,QString name);
    bool regist(QString mac);
    bool rename(QString mac,QString name);
    void constructor();

    void thread();

    void waitthread();
    void updatethread();



signals:
    void start();
    void next();
    void isexit();

};

#endif // ONLINE_H
