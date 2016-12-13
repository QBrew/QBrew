#include "menubar.h"

menubar::menubar(QWidget * parent) : QMenuBar(parent)
{
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
    connect(preferencesAction_,    &QAction::triggered, this,
            &menubar::preferencesPopup);
}

void menubar::aboutPopup()
{
    about * popup = new about(this);
    popup->exec();
}

void menubar::preferencesPopup()
{
    preferences * popup = new preferences(this);
    popup->exec();
}
