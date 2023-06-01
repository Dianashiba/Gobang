#include "eveScene.h"
#include <QMessageBox>
#include <Qlabel>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include <windows.h>
#include <QMouseEvent>
//int m=1;
eveScene::eveScene()
{
    //ai对ai的游戏模式
    aiToAi->setParent(this);
    aiToAi->setGeometry(QRect(50, 500, 121, 121));
    aiToAi->show();

    //设置重新开始按钮
    againBtn->setParent(this);
    againBtn->setGeometry(QRect(50, 750, 121, 121));
    againBtn->hide();

    //链接ai to ai的按钮
    connect(aiToAi,&QPushButton::clicked,[=](){
        aiToAi->zoomDown();
        aiToAi->zoomUp();
        againBtn->show();
        int i=1;
        int chessX=rand()%10+10;
        int chessY=rand()%10+10;
        chess[chessX][chessY]=i;
        update();
        return;

    });

    //链接重新开始按钮
    connect(againBtn,&QPushButton::clicked,[=](){
        againBtn->zoomDown();
        againBtn->zoomUp();
        QTimer::singleShot(400,this,[=](){
            constructor();
        });
    });
}
int eveScene::chessType(int rotate, int i, int j)
{
    if(aiFlag==1){
        int t,count=0;
        moveByOne(rotate,&i,&j);
        if((i<0||i>29)||(j<0||j>29))return -2;
        switch (chess[i][j]) {
        case 2:
        {
            while (chess[i][j]==2) {
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>29)||(j<0||j>29))
                {
                    t=count+9;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count-1;}
            else t=count+9;
        }break;
        case 1:
        {
            while(chess[i][j]==1){
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>29)||(j<0||j>29))
                {
                    t=count+109;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count+99;}
            else t=count+109;
        }break;
        case 0:
        {
            moveByOne(rotate,&i,&j);
            if((i<0||i>29)||(j<0||j>29))return -3;
            switch (chess[i][j]) {
            case 2:
            {
                while (chess[i][j]==2) {
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>29)||(j<0||j>29))
                    {
                        t=count+29;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+19;}
                else t=count+29;
            }break;
            case 1:
            {
                while(chess[i][j]==1){
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>29)||(j<0||j>29))
                    {
                        t=count+129;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+119;}
                else t=count+129;
            }break;
            case 0:{
                t=-1;
            }break;
            }
        }break;
        }
        return t;
    }else if(aiFlag==2){
        int t,count=0;
        moveByOne(rotate,&i,&j);
        if((i<0||i>29)||(j<0||j>29))return -2;
        switch (chess[i][j]) {
        case 1:
        {
            while (chess[i][j]==1) {
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>29)||(j<0||j>29))
                {
                    t=count+9;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count-1;}
            else t=count+9;
        }break;
        case 2:
        {
            while(chess[i][j]==2){
                ++count;moveByOne(rotate,&i,&j);
                if((i<0||i>29)||(j<0||j>29))
                {
                    t=count+109;
                    return t;
                }
            }
            if(chess[i][j]==0) {t=count+99;}
            else t=count+109;
        }break;
        case 0:
        {
            moveByOne(rotate,&i,&j);
            if((i<0||i>29)||(j<0||j>29))return -3;
            switch (chess[i][j]) {
            case 1:
            {
                while (chess[i][j]==1) {
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>29)||(j<0||j>29))
                    {
                        t=count+29;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+19;}
                else t=count+29;
            }break;
            case 2:
            {
                while(chess[i][j]==2){
                    ++count;moveByOne(rotate,&i,&j);
                    if((i<0||i>29)||(j<0||j>29))
                    {
                        t=count+129;
                        return t;
                    }
                }
                if(chess[i][j]==0) {t=count+119;}
                else t=count+129;
            }break;
            case 0:{
                t=-1;
            }break;
            }
        }break;
        }
        return t;
    }
}
void eveScene::mousePressEvent(QMouseEvent *event){
    // 如果是鼠标左键按下
    if(event->button() == Qt::LeftButton){
        aiFlag=1;
        ai();
    }
    // 如果是鼠标右键按下
    else if(event->button() == Qt::RightButton){
        aiFlag=2;
        ai();
    }
        update();
}
void eveScene::ai(){
    int all=0;
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            all+=chess[i][j];
        }
    }
    chessX=15;
    chessY=15;
    if(!all){
        chess[15][15]=1;
        update();
        return;
    }

    int temp=0,maxsource=0;
    chessX=0;
    chessY=0;

    //查找权值最大的点
    for(int i=0;i<30;++i)
        for(int j=0;j<30;++j)
        {
            if(chess[i][j]==0)
            {
                temp=value(i,j);
                if(temp>=maxsource)
                {
                    chessX=i;
                    chessY=j;
                    maxsource=temp;
                }
            }
        }

    //下棋子

    chess[chessX][chessY]=aiFlag;
    //判断是否结束
    bool ifisend=this->isend();
    //如果已经结束进行结束操作
    if(ifisend){
        end();
    }
    update();
}
void eveScene::end(){
    int ret =0;
    //弹出胜负结果会话框
    ret = QMessageBox::information(this,
                                     "",
                                     "再来一局？",
                                     QMessageBox::Yes|QMessageBox::No,
                                     QMessageBox::Yes);



    //根据玩家判断做出选项
    if(ret==QMessageBox::Yes)
    {
        constructor();
        update();
    }
    else if(ret==QMessageBox::No)
    {
        emit this->back();
        this->hide();
    }
}
void eveScene::moveByOne(int rotate, int *i, int *j){
    switch (rotate){
    case 1:{
        ++*i;
    }
    break;
    case 2:{
        ++*i;
        --*j;
    }
    break;
    case 3:{
        --*j;
    }
    break;
    case 4:{
        --*i;
        --*j;
    }
    break;
    case 5:{
        --*i;
    }
    break;
    case 6:{
        --*i;
        ++*j;
    }
    break;
    case 7:{
        ++*j;
    }
    break;
    case 8:{
        ++*i;
        ++*j;
    }
    break;
    }
}
int eveScene::value(int i, int j){
    int rotate=1,Value=0,source1,source2,score1,score2,X1,X2,Y1,Y2,Z1,Z2,temp;

    /*排除临界的32种棋型，因为会不断检查是够决出胜负，所以图上最多的为四子连珠，分敌我两种情况，于是：
     *            己冲，己活
     *      |自己->己空冲，己空活
     * 棋型->
     *      |对手->对冲，对活
     *             对空冲，对空活
     * 又因为每种棋型又分1-4个子的四种情况,所以共有32种棋型
     * */
    //权重部分
    int V[2][4][4]={{{40,700,6000,20000},
                       {6,10,600,20000},
                       {20,670,5400,0},
                       {6,10,500,0}},

                      {{30,300,2500,15000},
                       {2,8,300,9000},
                       {26,160,0,0},
                       {4,20,300,0}}};
    //rotate代表角度，代表了八个方向;以向右为1，则逆时针分别有2，3，4，5，6，7，8
    while(rotate!=5)
    {
        source1=chessType(rotate,i,j);
        rotate+=4;
        source2=chessType(rotate,i,j);
        rotate-=3;       //分别代表两个相反方向的棋型

        //调整使source1<source2
        if(source1>source2){
            temp=source1;
            source1=source2;
            source2=temp;
        }

        score1=source1;
        score2=source2;

        Z1=score1%10;
        score1/=10;
        Y1=score1%10;
        score1/=10;
        X1=score1%10;

        Z2=score2%10;
        score2/=10;
        Y2=score2%10;
        score2/=10;
        X2=score2%10;

        //对边界空，边界冲，临界三种情况分别赋值
        if(source1==-1){
            if(source2<0){
                Value+=0;
                continue;
            }
            else {
                Value+=V[X2][Y2][Z2]+5;
                continue;
            }
        }
        if(source1==-2){
            if(source2<0){
                Value+=0;
                continue;
            }
            else {
                Value+=V[X2][Y2][Z2]/2;
                continue;
            }
        }
        if(source1==-3){
            if(source2<0){
                Value+=0;
                continue;
            }
            else {
                Value+=V[X2][Y2][Z2]/3;
                continue;
            }
        }
        //己活己活，己活己冲，对活对活，对活对冲四种情况赋值
        if(((source1>=0&&source1<=3)&&((source2>=0&&source2<=3)||(source2>=10&&source2<=13)))||((source1>=100&&source1<=103)&&((source2>=100&&source2<=103)||(source2>=110&&source2<=113))))
        {
            if(Z1+Z2>=2){
                Value+=V[X2][Y2][3];
                continue;
            }else {
                Value+=V[X2][Y2][Z1+Z2+1];
                continue;
            }
        }
        //己冲己冲 对冲对冲情况赋值  因为两边被封死，如果落子能凑出5个子，那应该给与极大的权值，不然凑不齐5子，权值为0
        if(((source1>=10&&source1<=13)&&(source2>=10&&source2<=13))||((source1>=110&&source1<=113)&&(source2>=110&&source2<=113)))
        {
            if(Z1+Z2>=2){
                Value+=10000;
                continue;
            }
            else{
                Value+=0;
                continue;
            }
        }
        //己活对活，己活对冲，己冲对活，己冲对冲
        if(((source1>=0&&source1<=3)&&((source2>=100&&source2<=103)||(source2>=110&&source2<=113)))||((source1>=10&&source1<=13)&&((source2>=100&&source2<=103)||(source2>=110&&source2<=113)))){
            if(Z1==3||Z2==3){
                Value+=10000;
                continue;
            }
            else {
                Value+=V[X2][Y2][Z2]+V[X1][Y1][Z1]/4;
                continue;
            }
        }else{
            Value+=V[X1][Y1][Z1]+V[X2][Y2][Z2];
        }
        continue;
    }
    return Value;
}
void eveScene::constructor(){
    //清空棋盘
    for(int i=0;i<30;i++){
        for(int j=0;j<30;j++){
            chess[i][j]=0;
        }
    }
    againBtn->hide();
    aiToAi->show();
    beginFlag=0;
    winFlag=0;
    colorFlag=0;
    aiFlag=0;
    update();
}
