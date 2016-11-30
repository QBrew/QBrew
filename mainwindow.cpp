#include "mainwindow.h"
#include "View/packagelist.h"
#include "View/packagemodel.h"
#include "View/menubar.h"

#include <QDebug>
#include <QLineEdit>

mainWindow::mainWindow(QWidget * parent) : QMainWindow(parent)
{
    stackedWidget_ = new QStackedWidget(this);

    packageList_ = new packageList(this);
    stackedWidget_->addWidget(packageList_);

    menuBar_       = new menubar(this);
    toolBar_       = new toolBar(this);
    statusBar_     = new QStatusBar(this);

    addToolBar(toolBar_);
    connectToolbar();
    setMenuBar(menuBar_);
    setStatusBar(statusBar_);
    setCentralWidget(stackedWidget_);
}

void mainWindow::selectAll()
{
    static_cast<packageModel *>(packageList_->model())->selectAll();
    //qDebug() << stackedWidget_->widget(0)->model().selectAll();
    //qDebug() << test;
}

void mainWindow::connectToolbar()
{
    connect(toolBar_, &toolBar::selectAllClicked, this, [this]
    {
        selectAll();
    });
}
