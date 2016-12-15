#include "packageitem.h"

#include <QStringList>

PackageItem::PackageItem(const QList<QVariant> & data, bool isFavourite,
                         PackageItem * parent)
{
    parentItem_ = parent;
    itemData_ = data;
    isChecked_ = false;
    isFavourite_ = isFavourite;
}

PackageItem::~PackageItem()
{
    qDeleteAll(childItems_);
}

void PackageItem::appendChild(PackageItem * item)
{
    childItems_.append(item);
}

PackageItem * PackageItem::child(int row)
{
    return childItems_.value(row);
}

int PackageItem::childCount() const
{
    return childItems_.count();
}

int PackageItem::columnCount() const
{
    return itemData_.count();
}

QVariant PackageItem::data(int column) const
{
    return itemData_.value(column);
}

PackageItem * PackageItem::parent()
{
    return parentItem_;
}

bool PackageItem::isChecked() const
{
    return isChecked_;
}

void PackageItem::setChecked(bool set)
{
    isChecked_ = set;
}

bool PackageItem::isFavourite() const
{
    return isFavourite_;
}

void PackageItem::setFavourite(bool set)
{
    isFavourite_ = set;
}

int PackageItem::row() const
{
    if (parentItem_)
        return parentItem_->childItems_.indexOf(const_cast<PackageItem *>(this));

    return 0;
}
