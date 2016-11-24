#include "qbrewapplication.h"

#include <QApplication>

qBrewApplication::qBrewApplication(int & argc, char * argv[]) :
    QApplication(argc, argv)
{
    mainWindow_ = new mainWindow();
    mainWindow_->show();
}
