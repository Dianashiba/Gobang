#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include "pvpscene.h"
#include "pvescene.h"
#include "evescene.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    ~MainWindow();
    pvpScene * playpvp = NULL;
    pveScene * playpve = NULL;
    eveScene * playeve = NULL;
    login * playponline = NULL;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
