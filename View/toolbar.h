#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QAction>
#include <QToolBar>

class toolBar : public QToolBar
{
    Q_OBJECT

    QAction * updateAction_;
    QAction * installAction_;
    QAction * uninstallAction_;
    QAction * favoriAction_;
    QAction * emailAction_;

    void setActions();
    void setConnections();
    void setStatusTips();
    void setToolTips();

  public:
    explicit toolBar(QWidget * parent = 0);

  signals:
    void updateClicked();
    void installClicked();
    void uninstallClicked();
    void addFavoriClicked();
};

#endif // TOOLBAR_H
