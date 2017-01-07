#ifndef QBREWAPPLICATION_H
#define QBREWAPPLICATION_H

/*!
 * \file qbrewapplication.h
 * \brief Application launcher
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QApplication>
#include "mainwindow.h"

class MainWindow;

/*!
 * \class QBrewApplication
 * \brief The application launcher
 */
class QBrewApplication : public QApplication
{
  public:
    /*!
     * \brief Constructor
     * \param argc number of parameters
     * \param argv list of parameters
     */
    QBrewApplication(int & argc, char * argv[]);
  private:

    /*!
     * \brief The main window widget
     */
    MainWindow * mainWindow_;
};

#endif // QBREWAPPLICATION_H
