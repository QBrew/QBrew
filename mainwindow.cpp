#include "mainwindow.h"
#include "View/packagelist.h"
#include "View/packagemodel.h"
#include "View/menubar.h"

#include <QDebug>
#include <QLineEdit>
#include <QProgressDialog>
#include <QThread>

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

    packageList_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(packageList_, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
}

void mainWindow::selectAllNone(bool isAll)
{
    static_cast<packageModel *>(packageList_->model())->selectAllNone(isAll);
}

void mainWindow::install()
{
    QProgressDialog * progress = new QProgressDialog("Downloading", "", 0, 100000);

    progress->setCancelButton(NULL);
    progress->setWindowModality(Qt::WindowModal);
    progress->show();

    for (int i = 0; i < 100000; i++)
    {
        progress->setValue(i);
        QThread::usleep(10);

        if (progress->wasCanceled())
            break;
    }

    progress->setLabelText("Installation");
}

void mainWindow::connectToolbar()
{
    connect(toolBar_, &toolBar::selectAllClicked, this, [this] {selectAllNone(true);});
    connect(toolBar_, &toolBar::selectNoneClicked, this, [this] {selectAllNone(false);});
    connect(toolBar_, &toolBar::installClicked, this, [this] {install();});
}

void mainWindow::onCustomContextMenu(const QPoint &point)
{
    QModelIndex index = packageList_->indexAt(point);
    if (index.isValid()) {
        QMenu* contextMenu = new QMenu(packageList_);
        QAction* select = new QAction("Select",contextMenu);
        contextMenu->addAction(select);
        contextMenu->exec(packageList_->mapToGlobal(point));
    }
}
