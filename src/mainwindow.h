#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H

/*!
 * \file mainwindow.h
 * \brief main application window
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QAction>

#include "view/navigationbar.h"
#include "view/toolbar.h"
#include "view/packagelist.h"
#include "view/infobar.h"

/*!
 * \namespace qbrew
 *
 * namespace for all application classes and functions
 */
using namespace qbrew;

/*!
 * \class MainWindow
 * \brief main application window
 *
 * The class responsible for the main window
 * of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    /*!
     * \brief Constructor
     * \param parent widget from which this window will depend
     *
     * Constructor for the class
     */
    explicit MainWindow(QWidget * parent = 0);

  signals:

  public slots:
    /*!
     * \brief Select all or none from packagelist
     * \param isAll true = select all, false = select none
     */
    void selectAllNone(bool isAll);

    /*!
     * \brief Install selected packages
     */
    void install();

    /*!
     * \brief Uninstall selected packages
     */
    void uninstall();

    /*!
     * \brief update action to update homebrew then database
     */
    void update();

    /*!
     * \brief Install/uninstall progress bar popup
     * \param install true = install, false = uninstall
     * \return Number of packages installed or uninstalled
     */
    int installOrUninstallDialog(bool install);

    /*!
     * \brief Update infobar with selected package information
     */
    void updateInfoBar();

    /*!
     * \brief Favourite or unfavourite selected packages
     * \param isFavourite true = favourite, false = unfavourite
     */
    void updateFavourite(bool isFavourite);

    /*!
     * \brief search packages from search field input
     */
    void searchPackages();

    /*!
     * \brief right click menu for a package
     * \param point position of click
     */
    void onCustomContextMenu(const QPoint & point);

    /*!
     * \brief View installed packages
     */
    void viewInstalled();

    /*!
     * \brief View favourite packages
     */
    void viewFavourite();

    /*!
     * \brief Set backgroundColor of given widget to given color
     * \param qWidget the widget to change the backgroundColor of
     * \param color The color of the new background
     */
    void setBackgroundColor(QWidget * qWidget, QRgb color);

    /*!
     * \brief Click on a package
     * \param row row of package in packagelist_
     */
    void tableItemClicked(int row);

    /*!
     * \brief Double click on package
     * \param row row of package in packagelist_
     */
    void tableItemDoubleClicked(int row);

  private:

    /*!
     * \brief the main layout of the window
     */
    QHBoxLayout * hbox_;

    /*!
     * \brief the root widget that contains the main layout
     */
    QWidget * root_;

    /*!
     * \brief The navigation bar connected to this window
     */
    NavigationBar * navigationBar_;

    /*!
     * \brief The widget used to display the package list
     */
    QStackedWidget * stackedWidget_;

    /*!
     * \brief The tool bar connected to this window
     */
    ToolBar     *    toolBar_;

    /*!
     * \brief the menu bar connected to this window
     */
    QMenuBar    *    menuBar_;

    /*!
     * \brief The status bar connected to this window
     */
    QStatusBar   *   statusBar_;

    /*!
     * \brief The list of homebrew packages this window will modify
     */
    PackageList * packagelist_;

    /*!
     * \brief the info bar connected to this window
     */
    infoBar * infoBar_;

    /*!
     * \brief Index to know which package in list has been right clicked_
     */
    QModelIndex clicked_;

    /*!
     * \brief Connect tool bar actions to their function
     */
    void connectToolBar();

    /*!
     * \brief Connect navigation bar actions to their function
     */
    void connectNavigationBar();

    /*!
     * \brief Connect info bar to its update function
     */
    void connectInfoBar();
};

#endif // MAINWINDOWS_H
