#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T12:12:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tlp-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp
TRANSLATIONS = en.ts

HEADERS  += mainwindow.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    data.qrc
