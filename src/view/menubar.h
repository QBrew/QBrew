#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include "../view/packagelist.h"
#include "../menu/about.h"
#include "../menu/preferences.h"

class MenuBar : public QMenuBar
{
  public:
    MenuBar(QWidget * parent, qbrew::PackageList * list);

    void setActions();
    void setConnections();

    void aboutPopup();
    void preferencesPopup();
    void importPopup();
    void exportPopup();

  signals:

  public slots:

  private:
    QMenu * menu_;
    QMenu * favourites_;

    QAction * aboutAction_;
    QAction * preferencesAction_;

    QAction * importFavourites_;
    QAction * exportFavourites_;

    qbrew::PackageList * list_;
};

#endif // MENUBAR_H
