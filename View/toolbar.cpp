#include "toolbar.h"

#include <QIcon>
#include <QtSvg>

toolBar::toolBar(QWidget * parent) : QToolBar(parent)
{
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    setActions();
    setStatusTips();
    setToolTips();
    setConnections();
    setMovable(false);
}

void toolBar::setActions()
{
    updateAction_ = addAction(QIcon(":/Icons/update"),    tr("Update"));

    addSeparator();

    installAction_ = addAction(QIcon(":/install"),  tr("Install"));
    uninstallAction_ = addAction(QIcon(":/delete"),        tr("Uninstall"));
    favoriAction_ = addAction(QIcon("://favori"), tr("Favori"));
}

void toolBar::setStatusTips()
{
    updateAction_->setStatusTip(tr("Update the list of packages"));
    installAction_->setStatusTip(tr("Install selected packages"));
    uninstallAction_->setStatusTip(tr("Uninstall selected packages"));
    favoriAction_->setStatusTip(tr("Add selected packages to favori"));
}

void toolBar::setToolTips()
{
    updateAction_->setToolTip(tr("Update the list of packages"));
    installAction_->setToolTip(tr("Install selected packages"));
    uninstallAction_->setToolTip(tr("Uninstall selected packages"));
    favoriAction_->setToolTip(tr("Add selected packages to favori"));
}

void toolBar::setConnections()
{
    connect(updateAction_,    &QAction::triggered, this, &toolBar::updateClicked);
    connect(installAction_,    &QAction::triggered, this,
            &toolBar::installClicked);
    connect(uninstallAction_,     &QAction::triggered, this,
            &toolBar::uninstallClicked);
    connect(favoriAction_,      &QAction::triggered, this,
            &toolBar::addFavoriClicked);
}
