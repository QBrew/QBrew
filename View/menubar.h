#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include "Menu/about.h"
#include <iostream>

class menubar : public QMenuBar
{
public:
     menubar(QWidget * parent);
     void setActions();
     void setConnections();
     void aboutPopup();

signals:

public slots:

private:
     QAction* aboutAction_;
     QAction* preferencesAction_;
     QMenu* menu_;
};

#endif // MENUBAR_H
