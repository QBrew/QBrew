#include "mainwindow.h"

#include "view/menubar.h"
#include "view/packagelist.h"
#include "util/process.h"
#include "db/db/dbactions.h"
#include "db/db/dbmanager.h"
#include "db/dto/packagedto.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QLineEdit>
#include <QProgressDialog>
#include <QThread>
#include <QButtonGroup>
#include <QMessageBox>
#include <QSqlDatabase>

using namespace qbrewutil;

namespace qbrewview
{

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    root_ = new QWidget();
    hbox_ = new QHBoxLayout();
    hbox_->setContentsMargins(0, 0, 0, 0);
    hbox_->setSpacing(0);

    stackedWidget_ = new QStackedWidget(this);

    packagelist_ = new PackageList(this);
    stackedWidget_->addWidget(packagelist_);
    infoBar_ = new InfoBar();

    navigationBar_ = new NavigationBar();
    setBackgroundColor(navigationBar_, 0x00f6f6f6);
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
            SLOT(tableItemClicked(int)));
    connect(packagelist_, SIGNAL(cellDoubleClicked(int, int)), this,
            SLOT(tableItemDoubleClicked(int)));

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

void MainWindow::update()
{
    QProgressDialog * progress = new QProgressDialog("", "Cancel", 0,
            3, this);

    progress->setWindowModality(Qt::WindowModal);

    progress->setMinimumDuration(0);
    progress->setLabelText("Save favourites");
    progress->setValue(0);
    progress->show();

    QList<PackageDTO> temp = getFavourites();

    progress->setLabelText("Update Homebrew");
    progress->setValue(1);
    updateHomebrew();

    progress->setLabelText("Update database");
    progress->setValue(2);
    dropTable();

    QSqlDatabase db = QSqlDatabase::database();
    if (db.tables().isEmpty())
    {
        createTable();
        createDB(true);
        createDB(false);
    }

    addListInstalled(list(true), true);
    addListInstalled(list(false), false);

    for (PackageDTO package : temp)
    {
        qbrewdb::updateFavourite(package);
    }
    progress->setValue(3);

    packagelist_->update();
    infoBar_->clear();
}

int MainWindow::installOrUninstallDialog(bool install)
{
    QList<PackageDTO> selected = packagelist_->listSelected();
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
    QList<PackageDTO> selected = packagelist_->listSelected();
    for (PackageDTO f : selected)
    {
        f.setIsFavourite(isFavourite);
        qbrewdb::updateFavourite(f);
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

void MainWindow::setBackgroundColor(QWidget * qWidget, QRgb color)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    qWidget->setAutoFillBackground(true);
    qWidget->setPalette(pal);
}

void MainWindow::tableItemClicked(int row)
{
    packagelist_->tableItemClicked(row);
    packagelist_->setFocus();
}

void MainWindow::tableItemDoubleClicked(int row)
{
    packagelist_->tableItemDoubleClicked(row);
}

void MainWindow::connectToolBar()
{
    connect(toolBar_, &ToolBar::updateClicked, this, [this] {update();});
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
            tableItemDoubleClicked(clicked_.row());
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
            qbrewdb::updateFavourite(package);
            packagelist_->update();

        });
        contextMenu->addAction(select);
        contextMenu->addAction(install);
        contextMenu->addAction(favourite);
        contextMenu->exec(packagelist_->mapToGlobal(point));
    }
}

}
