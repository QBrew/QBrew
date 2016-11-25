#include "mainwindow.h"
#include "View/packagelist.h"
#include "View/packagemodel.h"

#include <QLineEdit>

mainWindow::mainWindow(QWidget * parent) : QMainWindow(parent)
{
    stackedWidget_ = new QStackedWidget(this);

    stackedWidget_->addWidget(new packageList(this));

    menuBar_       = new QMenuBar(this);
    toolBar_       = new toolBar(this);
    statusBar_     = new QStatusBar(this);

    addToolBar(toolBar_);
    setMenuBar(menuBar_);
    setStatusBar(statusBar_);
    setCentralWidget(stackedWidget_);
}
