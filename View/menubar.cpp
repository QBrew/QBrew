#include "menubar.h"

menubar::menubar(QWidget * parent) : QMenuBar(parent)
{
    //setIcon(QIcon(":/icons/medivisu.svg"));
    menu_ = new QMenu();
    setActions();
    setConnections();
    addMenu(menu_);
}

void menubar::setActions()
{
    aboutAction_ = menu_->addAction(tr("About"));
    preferencesAction_    = menu_->addAction(tr("Preferences"));
}

void menubar::setConnections()
{
    connect(aboutAction_,    &QAction::triggered, this, &menubar::aboutPopup);
}

void menubar::aboutPopup()
{
    about * popup = new about(this);
    popup->exec();
}
