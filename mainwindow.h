#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H


#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QHBoxLayout>

#include "View/navigationbar.h"
#include "View/toolbar.h"
#include "View/packagelist.h"

class mainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    explicit mainWindow(QWidget * parent = 0);

  signals:

  public slots:

    void selectAllNone(bool isAll);
    void install();
    void onCustomContextMenu(const QPoint &point);

    void viewAll();
    void viewInstalled();
    void viewFavourite();

  private:

    QHBoxLayout * hbox_;
    QWidget * root_;
    navigationBar * navigationBar_;
    QStackedWidget * stackedWidget_;
    toolBar     *    toolBar_;
    QMenuBar    *    menuBar_;
    QStatusBar   *   statusBar_;
    packageList * packageList_;

    void connectToolbar();
    void connectNavigationBar();
};

#endif // MAINWINDOWS_H
