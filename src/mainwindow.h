#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H


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

using namespace qbrew;

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    explicit MainWindow(QWidget * parent = 0);

  signals:

  public slots:

    void selectAllNone(bool isAll);

    void install();
    void uninstall();
    void updateInfoBar();
    void updateFavorite(bool isFavorite);
    void searchPackages();

    void onCustomContextMenu(const QPoint & point);

    void viewInstalled();
    void viewFavourite();

    void tableItemClicked(int row, int column);
    void tableItemDoubleClicked(int row, int column);

  private:

    QHBoxLayout * hbox_;
    QWidget * root_;
    NavigationBar * navigationBar_;
    QStackedWidget * stackedWidget_;
    ToolBar     *    toolBar_;
    QMenuBar    *    menuBar_;
    QStatusBar   *   statusBar_;
    PackageList * packagelist_;
    infoBar * infoBar_;

    QModelIndex clicked_;

    void connectToolbar();
    void connectNavigationBar();
};

#endif // MAINWINDOWS_H
