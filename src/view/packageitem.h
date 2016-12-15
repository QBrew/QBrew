#ifndef PACKAGEITEM_H
#define PACKAGEITEM_H

#include <QList>
#include <QVariant>

class PackageItem
{
  public:
    PackageItem(const QList<QVariant> & data, bool isFavourite,
                PackageItem * parent = 0);
    ~PackageItem();

    void appendChild(PackageItem * child);

    PackageItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    PackageItem * parent();
    bool isChecked() const;
    void setChecked(bool set);
    bool isFavourite() const;
    void setFavourite(bool set);

  private:
    QList<PackageItem *> childItems_;
    QList<QVariant> itemData_;
    PackageItem * parentItem_;
    bool isChecked_;
    bool isFavourite_;
};

#endif // PACKAGEITEM_H
