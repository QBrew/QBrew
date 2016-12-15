#include "qbrewapplication.h"

#include <QApplication>

QBrewApplication::QBrewApplication(int & argc, char * argv[]) :
    QApplication(argc, argv)
{
    mainWindow_ = new MainWindow();
    mainWindow_->show();
}
