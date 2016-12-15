#ifndef QBREWAPPLICATION_H
#define QBREWAPPLICATION_H


#include <QApplication>

#include "mainwindow.h"

class MainWindow;

class QBrewApplication : public QApplication
{
  public:
    QBrewApplication(int & argc, char * argv[]);
  private:
    MainWindow * mainWindow_;
};

#endif // QBREWAPPLICATION_H
