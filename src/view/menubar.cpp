#include "menubar.h"

MenuBar::MenuBar(QWidget * parent) : QMenuBar(parent)
{
    menu_ = new QMenu();
    setActions();
    setConnections();
    addMenu(menu_);
}

void MenuBar::setActions()
{
    aboutAction_ = menu_->addAction(tr("About"));
    preferencesAction_    = menu_->addAction(tr("Preferences"));
}

void MenuBar::setConnections()
{
    connect(aboutAction_,    &QAction::triggered, this, &MenuBar::aboutPopup);
    connect(preferencesAction_,    &QAction::triggered, this,
            &MenuBar::preferencesPopup);
}

void MenuBar::aboutPopup()
{
    About * popup = new About(this);
    popup->exec();
}

void MenuBar::preferencesPopup()
{
    Preferences * popup = new Preferences(this);
    popup->exec();
}
