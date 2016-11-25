#ifndef PACKAGEITEM_H
#define PACKAGEITEM_H

#include <QList>
#include <QVariant>

class packageItem
{
  public:
    packageItem(const QList<QVariant> & data, bool isFavourite,
                packageItem * parent = 0);
    ~packageItem();

    void appendChild(packageItem * child);

    packageItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    packageItem * parent();
    bool isChecked() const;
    void setChecked(bool set);
    bool isFavourite() const;
    void setFavourite(bool set);

  private:
    QList<packageItem *> childItems_;
    QList<QVariant> itemData_;
    packageItem * parentItem_;
    bool isChecked_;
    bool isFavourite_;
};

#endif // PACKAGEITEM_H
