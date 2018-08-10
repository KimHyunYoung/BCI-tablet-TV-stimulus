#-------------------------------------------------
#
# Project created by QtCreator 2017-07-28T13:47:24
#
#-------------------------------------------------

QT       += core gui serialport
QT       += multimedia
QT       += multimediawidgets
QT       += core widgets network concurrent
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Final1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tvwindow.cpp \
    on_off.cpp \
    doorlock.cpp \
    doorlockwindow.cpp \
    lightwindow.cpp \
    light.cpp

HEADERS += \
        mainwindow.h \
    tvwindow.h \
    on_off.h \
    doorlock.h \
    doorlockwindow.h \
    lightwindow.h \
    light.h

FORMS += \
        mainwindow.ui \
    tvwindow.ui \
    on_off.ui \
    doorlock.ui \
    light.ui \
    doorlockwindow.ui \
    lightwindow.ui
