/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *username;
    QLabel *userisfound;
    QLineEdit *edit;
    QPushButton *rename;
    QLabel *label;
    QPushButton *regist;
    QPushButton *registrandom;
    QPushButton *start;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->setEnabled(true);
        login->resize(400, 300);
        login->setMinimumSize(QSize(400, 300));
        login->setMaximumSize(QSize(400, 300));
        username = new QLabel(login);
        username->setObjectName("username");
        username->setGeometry(QRect(30, 20, 231, 31));
        userisfound = new QLabel(login);
        userisfound->setObjectName("userisfound");
        userisfound->setGeometry(QRect(280, 20, 101, 31));
        edit = new QLineEdit(login);
        edit->setObjectName("edit");
        edit->setGeometry(QRect(150, 90, 121, 21));
        rename = new QPushButton(login);
        rename->setObjectName("rename");
        rename->setGeometry(QRect(160, 140, 101, 21));
        label = new QLabel(login);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 90, 61, 21));
        regist = new QPushButton(login);
        regist->setObjectName("regist");
        regist->setGeometry(QRect(180, 190, 111, 21));
        registrandom = new QPushButton(login);
        registrandom->setObjectName("registrandom");
        registrandom->setGeometry(QRect(49, 190, 101, 21));
        start = new QPushButton(login);
        start->setObjectName("start");
        start->setGeometry(QRect(90, 230, 181, 31));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Form", nullptr));
        username->setText(QCoreApplication::translate("login", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">TextLabel</span></p></body></html>", nullptr));
        userisfound->setText(QCoreApplication::translate("login", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:700; color:#ff0000;\">TextLabel</span></p></body></html>", nullptr));
        rename->setText(QCoreApplication::translate("login", "\351\207\215\345\221\275\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("login", "username:", nullptr));
        regist->setText(QCoreApplication::translate("login", "\346\263\250\345\206\214", nullptr));
        registrandom->setText(QCoreApplication::translate("login", "\351\232\217\346\234\272\347\224\250\346\210\267\345\220\215\346\263\250\345\206\214", nullptr));
        start->setText(QCoreApplication::translate("login", "\350\277\233\345\205\245\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
