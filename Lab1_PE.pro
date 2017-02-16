#-------------------------------------------------
#
# Project created by QtCreator 2017-02-04T15:06:39
#
#-------------------------------------------------

QT       += core gui \
            charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1_PE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp \
    startwindow.cpp \
    graphwindow.cpp

HEADERS  += mainwindow.h \
    tablemodel.h \
    startwindow.h \
    graphwindow.h

FORMS    += mainwindow.ui \
    startwindow.ui \
    graphwindow.ui

DISTFILES +=
