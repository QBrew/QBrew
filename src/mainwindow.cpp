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
    infoBar_ = new infoBar();

    navigationBar_ = new NavigationBar();
    hbox_->addWidget(navigationBar_);
    QVBoxLayout * vBox = new QVBoxLayout();
    vBox->addWidget(stackedWidget_);
    vBox->addWidget(infoBar_);
    hbox_->addLayout(vBox);
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
    infoBar_->clear();
}

void MainWindow::install()
{
}

void MainWindow::uninstall()
{
}

void MainWindow::updateInfoBar()
{
    infoBar_->updateInfo(packagelist_->getSelected());
}

void MainWindow::updateFavorite(bool isFavorite)
{
    QList<qbrew::PackageDTO> selected = packagelist_->getListSelected();
    for (qbrew::PackageDTO f : selected)
    {
        f.setIsFavorite(isFavorite);
        qbrew::updateFavorite(f);
    }
    packagelist_->update();
    if (packagelist_->getStatus() == "Favorite")
    {
        infoBar_->clear();
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
        packagelist_->setSearch(searchText);
    }
}

void MainWindow::viewInstalled()
{
    packagelist_->setInstalled();
    infoBar_->clear();
}

void MainWindow::viewFavourite()
{
    packagelist_->setFavorite();
    infoBar_->clear();
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
    connect(toolBar_, &ToolBar::uninstallClicked, this, [this] {uninstall();});
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
    connect(packagelist_, &PackageList::clickedItemChange, this, [this] {updateInfoBar();});
}

void MainWindow::onCustomContextMenu(const QPoint & point)
{
    QModelIndex index = packagelist_->indexAt(point);
    if (index.isValid())
    {
        clicked_ = index;
        QMenu * contextMenu = new QMenu(packagelist_);
        QAction * select;
        select = new QAction("Select/Unselect", contextMenu);
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
