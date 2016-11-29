#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T15:01:41
#
#-------------------------------------------------

QT       += core gui sql svg

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql

TARGET = QBrew
TEMPLATE = app

SOURCES += main.cpp\
    Process/process.cpp \
    qbrewapplication.cpp \
    mainwindow.cpp \
    View/toolbar.cpp \
    View/packageitem.cpp \
    View/packagelist.cpp \
    View/packagemodel.cpp \
    DB/db.cpp \
    View/menubar.cpp \
    Menu/about.cpp

HEADERS  += \
    Process/process.h \
    View/packagelist.h \
    qbrewapplication.h \
    View/toolbar.h \
    View/packageitem.h \
    View/packagemodel.h \
    mainwindow.h \
    DB/db.h \
    DB/formula.h \
    View/menubar.h \
    Menu/about.h

FORMS    +=

RESOURCES += \
    ressources.qrc

DISTFILES +=
