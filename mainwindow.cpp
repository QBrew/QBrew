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
    root_ = new QWidget();
    hbox_ = new QHBoxLayout();
    hbox_->setContentsMargins(0, 0, 0, 0);
    hbox_->setSpacing(0);

    stackedWidget_ = new QStackedWidget(this);

    packageList_ = new packageList(this);
    stackedWidget_->addWidget(packageList_);
    navigationBar_ = new navigationBar();
    hbox_->addWidget(navigationBar_);
    hbox_->addWidget(stackedWidget_);
    root_->setLayout(hbox_);

    menuBar_       = new menubar(this);
    toolBar_       = new toolBar(this);
    statusBar_     = new QStatusBar(this);

    addToolBar(toolBar_);
    connectToolbar();
    connectNavigationBar();
    setMenuBar(menuBar_);
    setStatusBar(statusBar_);
    setCentralWidget(root_);

    packageList_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(packageList_, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onCustomContextMenu(const QPoint &)));
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

void mainWindow::viewAll()
{
    qDebug() << "ALL";
}

void mainWindow::viewInstalled()
{
    qDebug() << "INSTALL";
}

void mainWindow::viewFavourite()
{
    qDebug() << "FAVOURITE";
}

void mainWindow::connectToolbar()
{
    connect(toolBar_, &toolBar::selectAllClicked, this, [this] {selectAllNone(true);});
    connect(toolBar_, &toolBar::selectNoneClicked, this, [this] {selectAllNone(false);});
    connect(toolBar_, &toolBar::installClicked, this, [this] {install();});
}

void mainWindow::onCustomContextMenu(const QPoint & point)
{
    QModelIndex index = packageList_->indexAt(point);
    if (index.isValid())
    {
        QMenu * contextMenu = new QMenu(packageList_);
        QAction * select = new QAction("Select", contextMenu);
        contextMenu->addAction(select);
        contextMenu->exec(packageList_->mapToGlobal(point));
    }
}

void mainWindow::connectNavigationBar()
{
    connect(navigationBar_->all(), SIGNAL(clicked(bool)), this, SLOT(viewAll()));
    connect(navigationBar_->installed(), SIGNAL(clicked(bool)), this,
            SLOT(viewInstalled()));
    connect(navigationBar_->favourite(), SIGNAL(clicked(bool)), this,
            SLOT(viewFavourite()));
}
