#ifndef QBREWAPPLICATION_H
#define QBREWAPPLICATION_H


#include <QApplication>

#include "mainwindows.h"

class MainWindow;

class qBrewApplication : public QApplication
{
  public:
    qBrewApplication(int & argc, char * argv[]);
  private:
    mainWindow * mainWindow_;
};

#endif // QBREWAPPLICATION_H
