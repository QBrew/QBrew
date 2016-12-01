#ifndef MAINWINDOWS_H
#define MAINWINDOWS_H


#include <QMainWindow>
#include <QStackedWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

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

  private:

    QStackedWidget * stackedWidget_;
    toolBar     *    toolBar_;
    QMenuBar    *    menuBar_;
    QStatusBar   *   statusBar_;
    packageList * packageList_;
    void connectToolbar();
};

#endif // MAINWINDOWS_H
