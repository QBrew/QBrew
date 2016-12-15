#ifndef PACKAGELIST_H
#define PACKAGELIST_H

#include <QTreeView>

class PackageList : public QTreeView
{
    Q_OBJECT

    //void setHeaderLabels();
    void setTreeView();

  public:
    explicit PackageList(QWidget * parent = 0);

  signals:

  public slots:
};

#endif // PACKAGELIST_H
