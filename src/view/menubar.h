#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include "../menu/about.h"
#include <iostream>
#include "../menu/preferences.h"

class MenuBar : public QMenuBar
{
  public:
    MenuBar(QWidget * parent);
    void setActions();
    void setConnections();
    void aboutPopup();
    void preferencesPopup();

  signals:

  public slots:

  private:
    QAction * aboutAction_;
    QAction * preferencesAction_;
    QMenu * menu_;
};

#endif // MENUBAR_H
