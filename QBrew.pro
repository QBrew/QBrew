#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T15:01:41
#
#-------------------------------------------------

QT       += core gui sql svg

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBrew
TEMPLATE = app

SOURCES += src/main.cpp\
    src/process/process.cpp \
    src/qbrewapplication.cpp \
    src/mainwindow.cpp \
    src/view/toolbar.cpp \
    src/db/db/dbmanager.cpp \
    src/view/menubar.cpp \
    src/menu/about.cpp \
    src/menu/preferences.cpp \
    src/db/db/qbrewdb.cpp \
    src/view/navigationbar.cpp \
    src/db/dto/packagedto.cpp \
    src/view/packagelist.cpp \
    src/view/infobar.cpp

HEADERS  += \
    src/process/process.h \
    src/qbrewapplication.h \
    src/view/toolbar.h \
    src/mainwindow.h \
    src/db/db/dbmanager.h \
    src/view/menubar.h \
    src/menu/about.h \
    src/view/navigationbar.h \
    src/menu/preferences.h \
    src/db/db/qbrewdb.h \
    src/db/dto/packagedto.h \
    src/view/packagelist.h \
    src/view/infobar.h

FORMS    +=

RESOURCES += \
    ressources.qrc
