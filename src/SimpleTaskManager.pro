#-------------------------------------------------
#
# Project created by QtCreator 2013-06-29T20:19:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleTaskManager
TEMPLATE = app


SOURCES += main.cpp\
        mainscreen.cpp \
    simpletask.cpp \
    simpletasklistwidget.cpp

HEADERS  += mainscreen.h \
    simpletask.h \
    simpletasklistwidget.h

FORMS    += mainscreen.ui \
    simpletasklistwidget.ui

CONFIG += mobility
MOBILITY = 

