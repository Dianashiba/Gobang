#include "online.h"

online::online(QObject *parent)
    : QObject{parent}
{


}

//更新棋盘
int online::chessupdate(){
    QNetworkAccessManager manager;
    QUrl url("http://192.168.230.130:1211/update"); //局域网   http://192.168.230.130:1211/
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return 3 ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(response);

    bool flag=0;
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            if(chess[i][j]==doc["chess"][i][j].toInt())continue;
            flag=1;

        }
    }

    if(flag){
        for(int i=0;i<30;i++){
            for(int j=0;j<30;j++){
                chess[i][j]=doc["chess"][i][j].toInt();
            }
        }
        qDebug()<<"update  1";
        return 1;
    }
    return 0;

}

bool online::wait(QString mac,int color){
    QString waiturl="http://192.168.230.130:1211/wait";
    if(color==1){
        waiturl+="?color=black";
    }else{
        waiturl+="?color=white";
    }
    waiturl+="&mac=";
    waiturl+=mac;

    QNetworkAccessManager manager;
    QUrl url(waiturl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return false ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QString r=response;
    qDebug()<<r;
    if(r=="\"wait\""||r=="\"begin\"")return true;
    return false;
}

bool online::up(QString mac,int value,int h,int l){
    QString upurl="http://192.168.230.130:1211/up";
    upurl+="?value=";
    upurl+=QString::number(value);
    upurl+="&mac=";
    upurl+=mac;
    upurl+="&h=";
    upurl+=QString::number(h);
    upurl+="&l=";
    upurl+=QString::number(l);


    QNetworkAccessManager manager;
    QUrl url(upurl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return false ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QString r=response;
    qDebug()<<r;
    if(r=="\"ok\"")return true;
    return false;
}

bool online::exit(QString mac){
    QString exiturl="http://192.168.230.130:1211/exit";
    exiturl+="?mac=";
    exiturl+=mac;

    QNetworkAccessManager manager;
    QUrl url(exiturl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return false ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QString r=response;
    qDebug()<<r;
    if(r=="\"success\"")return true;
    return false;
}

bool online::isfound(QString mac){
    QString isfoundurl="http://192.168.230.130:1211/find";
    isfoundurl+="?mac=";
    isfoundurl+=mac;

    QNetworkAccessManager manager;
    QUrl url(isfoundurl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return false ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QString r=response;
    qDebug()<<r;
    if(r=="\"not found\"")return false;
    return true;
}

QString online::find(QString mac){
    QString findurl="http://192.168.230.130:1211/find";
    findurl+="?mac=";
    findurl+=mac;

    QNetworkAccessManager manager;
    QUrl url(findurl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return "" ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(response);
    return doc["name"].toString();
}

bool online::regist(QString mac,QString name){
    QString registurl="http://192.168.230.130:1211/register";
    registurl+="?mac=";
    registurl+=mac;
    registurl+="&name=";
    registurl+=name;


    QNetworkAccessManager manager;
    QUrl url(registurl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return false ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(response);
    qDebug()<<doc;
    return true;
}
bool online::regist(QString mac){
    QString registurl="http://192.168.230.130:1211/register";
    registurl+="?mac=";
    registurl+=mac;

    QNetworkAccessManager manager;
    QUrl url(registurl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return false ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(response);
    qDebug()<<doc;
    return true;
}

bool online::rename(QString mac,QString name){
    QString registurl="http://192.168.230.130:1211/rename";
    registurl+="?mac=";
    registurl+=mac;
    registurl+="&name=";
    registurl+=name;

    QNetworkAccessManager manager;
    QUrl url(registurl);
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error:" << reply->errorString();
        reply->deleteLater();
        return false ;
    }

    QByteArray response = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(response);
    qDebug()<<doc;
    return true;
}

//初始化函数
void online::constructor(){
    //初始化棋盘数组
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            chess[i][j]=0;
        }
    }
}
