#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T23:15:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = todolist5
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    addnewtaskwindow.cpp \
    taskdetailswindow.cpp \
    search_window.cpp \
    form.cpp

HEADERS += \
        mainwindow.h \
    addnewtaskwindow.h \
    taskdetailswindow.h \
    search_window.h \
    form.h

FORMS += \
        mainwindow.ui \
    addnewtaskwindow.ui \
    taskdetailswindow.ui \
    search_window.ui \
    form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES +=  widgets_icons.qrc
