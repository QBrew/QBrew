#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include "Menu/about.h"
#include <iostream>
#include "Menu/preferences.h"

class menubar : public QMenuBar
{
public:
     menubar(QWidget * parent);
     void setActions();
     void setConnections();
     void aboutPopup();
     void preferencesPopup();

signals:

public slots:

private:
     QAction* aboutAction_;
     QAction* preferencesAction_;
     QMenu* menu_;
};

#endif // MENUBAR_H
