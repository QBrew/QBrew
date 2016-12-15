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

SOURCES += src/main.cpp\
    src/process/process.cpp \
    src/qbrewapplication.cpp \
    src/mainwindow.cpp \
    src/view/toolbar.cpp \
    src/view/packageitem.cpp \
    src/view/packagelist.cpp \
    src/view/packagemodel.cpp \
    src/db/db/dbmanager.cpp \
    src/view/menubar.cpp \
    src/menu/about.cpp \
    src/menu/preferences.cpp \
    src/db/db/qbrewdb.cpp \
    src/db/dto/formuladto.cpp \
    src/view/navigationbar.cpp

HEADERS  += \
    src/process/process.h \
    src/view/packagelist.h \
    src/qbrewapplication.h \
    src/view/toolbar.h \
    src/view/packageitem.h \
    src/view/packagemodel.h \
    src/mainwindow.h \
    src/db/db/dbmanager.h \
    src/view/menubar.h \
    src/menu/about.h \
    src/view/navigationbar.h \
    src/db/dto/formuladto.h \
    src/menu/preferences.h \
    src/db/db/qbrewdb.h

FORMS    +=

RESOURCES += \
    ressources.qrc
