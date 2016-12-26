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

    //packageList_->setContextMenuPolicy(Qt::CustomContextMenu);
    /*connect(packageList_, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onCustomContextMenu(const QPoint &)));*/

    connect(formulalist_, SIGNAL(cellClicked(int, int)), this,
            SLOT(tableItemClicked(int, int)));
    connect(formulalist_, SIGNAL(cellDoubleClicked(int, int)), this,
            SLOT(tableItemDoubleClicked(int, int)));

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
    QList<qbrew::FormulaDTO> selected = formulalist_->getSelected();
    for (qbrew::FormulaDTO f : selected)
    {
        qbrew::addFavorite(f);
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

void MainWindow::viewSearch()
{
    formulalist_->setRowCount(0);
    QInputDialog * qid = new QInputDialog;
    QString text = QInputDialog::getText(this, tr("Search"),
                                         "Name or part of name\n(at least 3 characters)");
    if (text.size() > 3)
    {
        formulalist_->search(text);
    }
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
}

void MainWindow::onCustomContextMenu(const QPoint & point)
{
    /*QModelIndex index = packageList_->indexAt(point);
    if (index.isValid())
    {
        QMenu * contextMenu = new QMenu(packageList_);
        QAction * select = new QAction("Select", contextMenu);
        contextMenu->addAction(select);
        contextMenu->exec(packageList_->mapToGlobal(point));
    }*/
}


void MainWindow::connectNavigationBar()
{
    connect(navigationBar_->all(), SIGNAL(clicked(bool)), this, SLOT(viewAll()));
    connect(navigationBar_->installed(), SIGNAL(clicked(bool)), this,
            SLOT(viewInstalled()));
    connect(navigationBar_->favourite(), SIGNAL(clicked(bool)), this,
            SLOT(viewFavourite()));
    connect(navigationBar_->search(), SIGNAL(clicked(bool)), this,
            SLOT(viewSearch()));
}
