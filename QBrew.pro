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
    src/qbrewapplication.cpp \
    src/mainwindow.cpp \
    src/view/toolbar.cpp \
    src/view/menubar.cpp \
    src/view/navigationbar.cpp \
    src/view/packagelist.cpp \
    src/view/infobar.cpp \
    src/db/db/dbmanager.cpp \
    src/db/dto/packagedto.cpp \
    src/db/db/dbactions.cpp \
    src/menu/about.cpp \
    src/menu/preferences.cpp \
    src/util/process.cpp \
    src/util/settings.cpp

HEADERS  += \
    src/qbrewapplication.h \
    src/view/toolbar.h \
    src/view/menubar.h \
    src/view/navigationbar.h \
    src/view/packagelist.h \
    src/view/infobar.h \
    src/mainwindow.h \
    src/db/db/dbmanager.h \
    src/db/dto/packagedto.h \
    src/db/db/dbactions.h \
    src/menu/about.h \
    src/menu/preferences.h \
    src/util/process.h \
    src/util/settings.h

TRANSLATIONS = translations/qbrew_fr.ts

RESOURCES += \
    ressources.qrc
