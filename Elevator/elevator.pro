#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T11:53:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = elevator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    goingupdialog.cpp \
    goingdowndialog.cpp \
    queue.cpp \
    stack.cpp

HEADERS  += mainwindow.h \
    goingupdialog.h \
    goingdowndialog.h \
    queue.h \
    stack.h

FORMS    += mainwindow.ui \
    goingupdialog.ui \
    goingdowndialog.ui
