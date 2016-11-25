#include "packageitem.h"

#include <QStringList>

packageItem::packageItem(const QList<QVariant> & data, bool isFavourite,
                         packageItem * parent)
{
    parentItem_ = parent;
    itemData_ = data;
    isChecked_ = false;
    isFavourite_ = isFavourite;
}

packageItem::~packageItem()
{
    qDeleteAll(childItems_);
}

void packageItem::appendChild(packageItem * item)
{
    childItems_.append(item);
}

packageItem * packageItem::child(int row)
{
    return childItems_.value(row);
}

int packageItem::childCount() const
{
    return childItems_.count();
}

int packageItem::columnCount() const
{
    return itemData_.count();
}

QVariant packageItem::data(int column) const
{
    return itemData_.value(column);
}

packageItem * packageItem::parent()
{
    return parentItem_;
}

bool packageItem::isChecked() const
{
    return isChecked_;
}

void packageItem::setChecked(bool set)
{
    isChecked_ = set;
}

bool packageItem::isFavourite() const
{
    return isFavourite_;
}

void packageItem::setFavourite(bool set)
{
    isFavourite_ = set;
}

int packageItem::row() const
{
    if (parentItem_)
        return parentItem_->childItems_.indexOf(const_cast<packageItem *>(this));

    return 0;
}
