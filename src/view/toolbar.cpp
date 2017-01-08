#include "toolbar.h"

#include <QIcon>
#include <QtSvg>

ToolBar::ToolBar(QWidget * parent) : QToolBar(parent)
{
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    setActions();
    setSearchField();
    setStatusTips();
    setToolTips();
    setConnections();
    setMovable(false);
}

QLineEdit * ToolBar::searchField() const
{
    return searchField_;
}

void ToolBar::setActions()
{
    updateAction_ = addAction(QIcon(":/Icons/update"), tr("Update"));

    addSeparator();

    selectAll_ = addAction(QIcon(":/Icons/selectAll"), tr("Select all"));
    selectNone_ = addAction(QIcon(":/Icons/selectNone"), tr("Select none"));

    addSeparator();

    installAction_ = addAction(QIcon(":/Icons/install"),  tr("Install"));
    uninstallAction_ = addAction(QIcon(":/Icons/uninstall"),
                                 tr("Uninstall"));
    favouriteAction_ = addAction(QIcon(":/Icons/favourite"), tr("Favourite"));
    removeFavouriteAction_ = addAction(QIcon(":Icons/noFavourite"),
                                       tr("Remove\nfavourite"));
}

void ToolBar::setStatusTips()
{
    updateAction_->setStatusTip(tr("Update the list of packages"));
    selectAll_->setStatusTip(tr("Select all the packages listed"));
    selectNone_->setStatusTip(tr("Select none of the packages listed"));
    installAction_->setStatusTip(tr("Install selected packages"));
    uninstallAction_->setStatusTip(tr("Uninstall selected packages"));
    favouriteAction_->setStatusTip(tr("Add selected packages to favourite"));
    removeFavouriteAction_->setStatusTip(
        tr("Remove selected packages from favourite"));
    searchField_->setStatusTip(tr("Search a one or several packages"));
}

void ToolBar::setToolTips()
{
    updateAction_->setToolTip(tr("Update the list of packages"));
    selectAll_->setToolTip(tr("Select all the packages listed"));
    selectNone_->setToolTip(tr("Select none of the packages listed"));
    installAction_->setToolTip(tr("Install selected packages"));
    uninstallAction_->setToolTip(tr("Uninstall selected packages"));
    favouriteAction_->setToolTip(tr("Add selected packages to favourite"));
    removeFavouriteAction_->setToolTip(
        tr("Remove selected packages from favourite"));
    searchField_->setToolTip(tr("Search a one or several packages"));
}

void ToolBar::setSearchField()
{
    addSeparator();

    searchField_ = new QLineEdit();
    searchField_->setPlaceholderText("Search");
    searchField_->setMaximumWidth(200);
    addWidget(searchField_);
}

void ToolBar::setConnections()
{
    connect(updateAction_, &QAction::triggered,
            this, &ToolBar::updateClicked);
    connect(selectAll_, &QAction::triggered,
            this, &ToolBar::selectAllClicked);
    connect(selectNone_, &QAction::triggered,
            this, &ToolBar::selectNoneClicked);
    connect(installAction_, &QAction::triggered,
            this, &ToolBar::installClicked);
    connect(uninstallAction_, &QAction::triggered,
            this, &ToolBar::uninstallClicked);
    connect(favouriteAction_, &QAction::triggered,
            this, &ToolBar::addFavouriteClicked);
    connect(removeFavouriteAction_, &QAction::triggered,
            this, &ToolBar::removeFavouriteClicked);
    connect(searchField_, &QLineEdit::returnPressed,
            this, &ToolBar::searchPressed);
}
