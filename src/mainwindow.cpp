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
#include <QMessageBox>

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

    menuBar_       = new MenuBar(this, packagelist_);
    toolBar_       = new ToolBar(this);
    statusBar_     = new QStatusBar(this);

    addToolBar(toolBar_);
    connectToolBar();
    connectNavigationBar();
    connectInfoBar();

    setMenuBar(menuBar_);
    setStatusBar(statusBar_);
    setCentralWidget(root_);

    packagelist_->setFocus();
    showMaximized();

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
    int i = installOrUninstallDialog(true);
    QMessageBox message;
    message.setText(QString::number(i) +
                    " package(s) installed");
    message.setStandardButtons(QMessageBox::Ok);
    message.exec();
}

void MainWindow::uninstall()
{
    int i = installOrUninstallDialog(false);
    QMessageBox message;
    message.setText(QString::number(i) +
                    " package(s) removed");
    message.setStandardButtons(QMessageBox::Ok);
    message.exec();
}

int MainWindow::installOrUninstallDialog(bool install)
{
    QList<qbrew::PackageDTO> selected = packagelist_->listSelected();
    int number {0};
    QProgressDialog * progress = new QProgressDialog("", "Cancel", 0,
            selected.size(), this);

    progress->setWindowModality(Qt::WindowModal);

    progress->setMinimumDuration(0);
    progress->setLabelText(install ? "Installing ..." : "Uninstalling ...");
    progress->setValue(0);
    progress->show();

    for (int i = 0; i < selected.size(); i++)
    {
        progress->setValue(i);

        if (install && !selected.at(i).isInstalled())
        {
            if (true)
                //if (qbrew::install(selected.at(i)) == 0)
            {
                addInstalled(selected.at(i));
                number++;
            }
        }
        if (!install && selected.at(i).isInstalled())
        {
            if (true)
                //if (qbrew::uninstall(selected.at(i)) == 0)
            {
                removeInstalled(selected.at(i));
                number++;
            }
        }
        if (progress->wasCanceled())
            break;
        QThread::sleep(1);

    }
    progress->setValue(selected.size());
    progress->close();

    packagelist_->update();
    infoBar_->clear();
    return number;
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

void MainWindow::connectToolBar()
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
}

void MainWindow::connectInfoBar()
{
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
        select = new QAction("Select / Unselect", contextMenu);
        connect(select, &QAction::triggered, [this]()
        {
            tableItemDoubleClicked(clicked_.row(), 0);
        });
        QAction * install = new QAction("Install / Uninstall", contextMenu);
        connect(install, &QAction::triggered, [this]()
        {

        });
        QAction * favourite = new QAction("Favourite / Unfavourite", contextMenu);
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
