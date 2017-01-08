/*!
 * \file qbrewapplication.h
 * \brief Application launcher
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#ifndef QBREWAPPLICATION_H
#define QBREWAPPLICATION_H

#include <QApplication>
#include "mainwindow.h"

namespace qbrewview
{

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
     * \param argc Number of parameters
     * \param argv List of parameters
     */
    QBrewApplication(int & argc, char * argv[]);
  private:

    /*!
     * \brief The main window widget
     */
    MainWindow * mainWindow_;
};

}

#endif // QBREWAPPLICATION_H
