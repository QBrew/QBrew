#ifndef PACKAGELIST_H
#define PACKAGELIST_H

#include <QTreeView>

class packageList : public QTreeView
{
    Q_OBJECT

    //void setHeaderLabels();
    void setTreeView();

  public:
    explicit packageList(QWidget * parent = 0);

  signals:

  public slots:
};

#endif // PACKAGELIST_H
