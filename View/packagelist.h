#ifndef PACKAGELIST_H
#define PACKAGELIST_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QVariant>

#include <Process/process.h>

class packageList : public QTreeView
{
    Q_OBJECT

    void setHeaderLabels();
    void setTreeView();

  public:
    explicit packageList(QWidget * parent = 0);

    QVariant data(const QModelIndex & index, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;

  signals:

  public slots:
};

#endif // PACKAGELIST_H
