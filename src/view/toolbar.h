#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QAction>
#include <QToolBar>
#include <QLineEdit>

class ToolBar : public QToolBar
{
    Q_OBJECT

    QAction * updateAction_;
    QAction * installAction_;
    QAction * uninstallAction_;
    QAction * favoriAction_;
    QAction * emailAction_;
    QAction * selectAll_;
    QAction * selectNone_;

    QLineEdit * searchField_;

    void setActions();
    void setConnections();
    void setStatusTips();
    void setToolTips();
    void setSearchField();

  public:
    explicit ToolBar(QWidget * parent = 0);
    QLineEdit * searchField() const;

  signals:
    void updateClicked();
    void installClicked();
    void uninstallClicked();
    void addFavoriClicked();
    void selectAllClicked();
    void selectNoneClicked();
    void searchPressed();
};

#endif // TOOLBAR_H
