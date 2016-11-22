#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T15:01:41
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBrew
TEMPLATE = app


SOURCES += main.cpp\
        qbrew.cpp \
    Process/process.cpp

HEADERS  += qbrew.h \
    Process/process.h

FORMS    += qbrew.ui
