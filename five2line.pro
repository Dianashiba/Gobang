QT       += core gui
QT+=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseScene.cpp \
    evescene.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    mybutton.cpp \
    online.cpp \
    pvescene.cpp \
    pvponline.cpp \
    pvpscene.cpp

HEADERS += \
    BaseScene.h \
    evescene.h \
    login.h \
    mainwindow.h \
    mybutton.h \
    online.h \
    pvescene.h \
    pvponline.h \
    pvpscene.h

FORMS += \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res1.qrc
