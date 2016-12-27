#include "mainwindow.h"
#include "view/menubar.h"
#include "view/packagelist.h"

#include <QTableWidget>
#include <src/db/db/qbrewdb.h>
#include <src/db/dto/packagedto.h>
#include <QHeaderView>

#include <QInputDialog>

#include <QDebug>
#include <QLineEdit>
#include <QProgressDialog>
#include <QThread>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    root_ = new QWidget();
    hbox_ = new QHBoxLayout();
    hbox_->setContentsMargins(0, 0, 0, 0);
    hbox_->setSpacing(0);

    stackedWidget_ = new QStackedWidget(this);

    packagelist_ = new PackageList(this);
    stackedWidget_->addWidget(packagelist_);

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
    packagelist_->setFocus();

    connect(packagelist_, SIGNAL(cellClicked(int, int)), this,
            SLOT(tableItemClicked(int, int)));
    connect(packagelist_, SIGNAL(cellDoubleClicked(int, int)), this,
            SLOT(tableItemDoubleClicked(int, int)));

    packagelist_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(packagelist_, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onCustomContextMenu(const QPoint &)));


}

void MainWindow::selectAllNone(bool isAll)
{
    packagelist_->selectPackage(isAll);
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

void MainWindow::updateFavorite(bool isFavorite)
{
    QList<qbrew::PackageDTO> selected = packagelist_->getSelectedFavorite();
    for (qbrew::PackageDTO f : selected)
    {
        f.setIsFavorite(isFavorite);
        qbrew::updateFavorite(f);
    }
}

void MainWindow::searchPackages()
{
    QString searchText = toolBar_->searchField()->text();
    if (searchText.length() < 2)
    {
        toolBar_->searchField()->clear();
        toolBar_->searchField()->setPlaceholderText("At least 2 letters");
    }
    else
    {
        navigationBar_->group()->setExclusive(false);

        navigationBar_->installed()->setChecked(false);
        navigationBar_->favourite()->setChecked(false);
        navigationBar_->group()->setExclusive(true);

        toolBar_->searchField()->setPlaceholderText("Search");
        packagelist_->search(searchText);
    }
}

void MainWindow::viewInstalled()
{
    packagelist_->setInstalled();
}

void MainWindow::viewFavourite()
{
    packagelist_->setFavorite();
}

void MainWindow::tableItemClicked(int row, int column)
{
    packagelist_->tableItemClicked(row, column);
    packagelist_->setFocus();
}

void MainWindow::tableItemDoubleClicked(int row, int column)
{
    packagelist_->tableItemDoubleClicked(row, column);
}

void MainWindow::connectToolbar()
{
    connect(toolBar_, &ToolBar::selectAllClicked, this, [this] {selectAllNone(true);});
    connect(toolBar_, &ToolBar::selectNoneClicked, this, [this] {selectAllNone(false);});
    connect(toolBar_, &ToolBar::installClicked, this, [this] {install();});
    connect(toolBar_, &ToolBar::addFavoriClicked, this, [this] {updateFavorite(true);});
    connect(toolBar_, &ToolBar::removeFavouriteClicked, this, [this] {updateFavorite(false);});
    connect(toolBar_, &ToolBar::searchPressed, this, [this] {searchPackages();});
}

void MainWindow::connectNavigationBar()
{
    connect(navigationBar_->installed(), SIGNAL(clicked(bool)), this,
            SLOT(viewInstalled()));
    connect(navigationBar_->favourite(), SIGNAL(clicked(bool)), this,
            SLOT(viewFavourite()));
}

void MainWindow::onCustomContextMenu(const QPoint & point)
{
    QModelIndex index = packagelist_->indexAt(point);
    if (index.isValid())
    {
        clicked_ = index;
        QMenu * contextMenu = new QMenu(packagelist_);
        QCheckBox * check = (QCheckBox *)packagelist_->cellWidget(index.row(), 0);
        QAction * select;
        if (check->isChecked())
        {
            select = new QAction("Unselect", contextMenu);
        }
        else
        {
            select = new QAction("Select", contextMenu);
        }
        connect(select, &QAction::triggered, [this]()
        {
            tableItemDoubleClicked(clicked_.row(), 0);
        });
        QAction * install = new QAction("Install", contextMenu);
        QAction * favourite = new QAction("Favourite", contextMenu);
        contextMenu->addAction(select);
        contextMenu->addAction(install);
        contextMenu->addAction(favourite);
        contextMenu->exec(packagelist_->mapToGlobal(point));
    }
}
