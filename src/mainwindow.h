#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H


#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QHBoxLayout>

#include "view/navigationbar.h"
#include "view/toolbar.h"
#include "view/packagelist.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    explicit MainWindow(QWidget * parent = 0);

  signals:

  public slots:

    void selectAllNone(bool isAll);
    void install();
    void onCustomContextMenu(const QPoint & point);

    void viewAll();
    void viewInstalled();
    void viewFavourite();

  private:

    QHBoxLayout * hbox_;
    QWidget * root_;
    NavigationBar * navigationBar_;
    QStackedWidget * stackedWidget_;
    ToolBar     *    toolBar_;
    QMenuBar    *    menuBar_;
    QStatusBar   *   statusBar_;
    PackageList * packageList_;

    void connectToolbar();
    void connectNavigationBar();
};

#endif // MAINWINDOWS_H
