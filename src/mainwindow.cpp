#include "mainwindow.h"
#include "view/menubar.h"
#include "view/packagelist.h"
#include "process/process.h"

#include <QTableWidget>
#include <src/db/db/qbrewdb.h>
#include <src/db/dto/packagedto.h>
#include <QHeaderView>
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
    packagelist_->setSelectPackage(isAll);
    infoBar_->clear();
}

void MainWindow::install()
{
    progressDialog(true);
}

void MainWindow::uninstall()
{
    progressDialog(false);
}

void MainWindow::progressDialog(bool install)
{
    QList<qbrew::PackageDTO> selected = packagelist_->listSelected();

    QProgressDialog * progress = new QProgressDialog("", "", 0,
            selected.size());
    progress->setWindowTitle(install ? "Installing ..." : "Uninstalling ...");
    progress->setCancelButton(NULL);
    progress->setWindowModality(Qt::WindowModal);

    progress->setValue(0);
    progress->setLabelText("0/" + QString::number(selected.size()));
    QThread::sleep(2);

    for (int i = 0; i < selected.size(); i++)
    {
        QString label = QString::number(i + 1) + "/"
                        + QString::number(selected.size());
        label.append("\n" + selected.at(i).filename());
        progress->setLabelText(label);
        progress->setValue(i);
        QThread::sleep(2);

        if (install)
        {
            //qbrew::install(package);
        }
        else
        {
            //uninstall
        }

        if (progress->wasCanceled())
            break;
    }
    progress->setValue(selected.size());
    //cleanup
    //packagelist_->update();
}

void MainWindow::updateInfoBar()
{
    infoBar_->updateInfo(packagelist_->selected());
}

void MainWindow::updateFavourite(bool isFavourite)
{
    QList<qbrew::PackageDTO> selected = packagelist_->listSelected();
    for (qbrew::PackageDTO f : selected)
    {
        f.setIsFavourite(isFavourite);
        qbrew::updateFavourite(f);
    }
    packagelist_->update();
    if (packagelist_->getStatus() == "Favourite")
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
    packagelist_->setFavourite();
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
    connect(toolBar_, &ToolBar::addFavouriteClicked, this, [this] {updateFavourite(true);});
    connect(toolBar_, &ToolBar::removeFavouriteClicked, this, [this] {updateFavourite(false);});
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
        QAction * install = new QAction("Install/Uninstall", contextMenu);
        connect(install, &QAction::triggered, [this]()
        {

        });
        QAction * favourite = new QAction("Favourite/Unfavourite", contextMenu);
        connect(favourite, &QAction::triggered, [this]()
        {
            PackageDTO package = packagelist_->getPackage(clicked_.row());
            package.setIsFavourite(!package.isFavourite());
            qbrew::updateFavourite(package);
            packagelist_->update();

        });
        contextMenu->addAction(select);
        contextMenu->addAction(install);
        contextMenu->addAction(favourite);
        contextMenu->exec(packagelist_->mapToGlobal(point));
    }
}
