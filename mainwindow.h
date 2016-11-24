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

  private:

    QStackedWidget * stackedWidget_;
    toolBar     *    toolBar_;
    QMenuBar    *    menuBar_;
    QStatusBar   *   statusBar_;
};

#endif // MAINWINDOWS_H
