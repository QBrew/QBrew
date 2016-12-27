#include "mainwindow.h"
#include "view/menubar.h"
#include "view/formulalist.h"

#include <QTableWidget>
#include <src/db/DB/qbrewdb.h>
#include <src/db/DTO/formuladto.h>
#include <QHeaderView>

#include <QInputDialog>

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

    formulalist_ = new FormulaList(this);
    stackedWidget_->addWidget(formulalist_);

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
    formulalist_->setFocus();

    connect(formulalist_, SIGNAL(cellClicked(int, int)), this,
            SLOT(tableItemClicked(int, int)));
    connect(formulalist_, SIGNAL(cellDoubleClicked(int, int)), this,
            SLOT(tableItemDoubleClicked(int, int)));

    formulalist_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(formulalist_, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onCustomContextMenu(const QPoint &)));


}

void MainWindow::selectAllNone(bool isAll)
{
    formulalist_->selectFormula(isAll);
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

void MainWindow::addFavorite()
{
    QList<qbrew::FormulaDTO> selected = formulalist_->getSelectedFavorite();
    for (qbrew::FormulaDTO f : selected)
    {
        qbrew::addFavorite(f);
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
        navigationBar_->search()->setChecked(true);
        toolBar_->searchField()->setPlaceholderText("Search");
        formulalist_->search(searchText);
    }
}

void MainWindow::viewAll()
{
    //formulalist_->setAll()
}

void MainWindow::viewInstalled()
{
    formulalist_->setInstalled();
}

void MainWindow::viewFavourite()
{
    formulalist_->setFavorite();
}

void MainWindow::tableItemClicked(int row, int column)
{
    formulalist_->tableItemClicked(row, column);
    formulalist_->setFocus();
}

void MainWindow::tableItemDoubleClicked(int row, int column)
{
    formulalist_->tableItemDoubleClicked(row, column);
}

void MainWindow::connectToolbar()
{
    connect(toolBar_, &ToolBar::selectAllClicked, this, [this] {selectAllNone(true);});
    connect(toolBar_, &ToolBar::selectNoneClicked, this, [this] {selectAllNone(false);});
    connect(toolBar_, &ToolBar::installClicked, this, [this] {install();});
    connect(toolBar_, &ToolBar::addFavoriClicked, this, [this] {addFavorite();});
    connect(toolBar_, &ToolBar::searchPressed, this, [this] {searchPackages();});
}

void MainWindow::connectNavigationBar()
{
    connect(navigationBar_->all(), SIGNAL(clicked(bool)), this, SLOT(viewAll()));
    connect(navigationBar_->installed(), SIGNAL(clicked(bool)), this,
            SLOT(viewInstalled()));
    connect(navigationBar_->favourite(), SIGNAL(clicked(bool)), this,
            SLOT(viewFavourite()));
}

void MainWindow::onCustomContextMenu(const QPoint & point)
{
    QModelIndex index = formulalist_->indexAt(point);
    if (index.isValid())
    {
        clicked_ = index;
        QMenu * contextMenu = new QMenu(formulalist_);
        QCheckBox * check = (QCheckBox *)formulalist_->cellWidget(index.row(), 0);
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
        contextMenu->exec(formulalist_->mapToGlobal(point));
    }
}
