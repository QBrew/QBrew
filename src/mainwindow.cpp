#include "mainwindow.h"
#include "view/packagelist.h"
#include "view/packagemodel.h"
#include "view/menubar.h"

#include <QDebug>
#include <QLineEdit>
#include <QProgressDialog>
#include <QThread>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    root_ = new QWidget();
    hbox_ = new QHBoxLayout();
    hbox_->setContentsMargins(0, 0, 0, 0);
    hbox_->setSpacing(0);

    stackedWidget_ = new QStackedWidget(this);

    packageList_ = new PackageList(this);
    stackedWidget_->addWidget(packageList_);
    navigationBar_ = new NavigationBar();
    hbox_->addWidget(navigationBar_);
    hbox_->addWidget(stackedWidget_);
    root_->setLayout(hbox_);

    menuBar_       = new MenuBar(this);
    toolBar_       = new ToolBar(this);
    statusBar_     = new QStatusBar(this);

    addToolBar(toolBar_);
    connectToolbar();
    connectNavigationBar();
    setMenuBar(menuBar_);
    setStatusBar(statusBar_);
    setCentralWidget(root_);

    showMaximized();

    packageList_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(packageList_, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onCustomContextMenu(const QPoint &)));
}

void MainWindow::selectAllNone(bool isAll)
{
    static_cast<PackageModel *>(packageList_->model())->selectAllNone(isAll);
}

void MainWindow::install()
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

void MainWindow::viewAll()
{
    qDebug() << "ALL";
}

void MainWindow::viewInstalled()
{
    qDebug() << "INSTALL";
}

void MainWindow::viewFavourite()
{
    qDebug() << "FAVOURITE";
}

void MainWindow::connectToolbar()
{
    connect(toolBar_, &ToolBar::selectAllClicked, this, [this] {selectAllNone(true);});
    connect(toolBar_, &ToolBar::selectNoneClicked, this, [this] {selectAllNone(false);});
    connect(toolBar_, &ToolBar::installClicked, this, [this] {install();});
}

void MainWindow::onCustomContextMenu(const QPoint & point)
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

void MainWindow::connectNavigationBar()
{
    connect(navigationBar_->all(), SIGNAL(clicked(bool)), this, SLOT(viewAll()));
    connect(navigationBar_->installed(), SIGNAL(clicked(bool)), this,
            SLOT(viewInstalled()));
    connect(navigationBar_->favourite(), SIGNAL(clicked(bool)), this,
            SLOT(viewFavourite()));
}
