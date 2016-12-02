/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    packageModel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/
#include <QDebug>
#include <QIcon>
#include "packagemodel.h"

packageModel::packageModel(const QList<QMap<QString, QString>> & data,
                           QObject * parent)
{
    QList<QVariant> rootData;
    rootData << "Name" << "Version";
    rootItem_ = new packageItem(rootData, false);
    setupModelData(data, rootItem_);
}

packageModel::~packageModel()
{
    delete rootItem_;
}

int packageModel::columnCount(const QModelIndex & parent) const
{
    if (parent.isValid())
        return static_cast<packageItem *>(parent.internalPointer())->columnCount();
    else
        return rootItem_->columnCount();
}

QVariant packageModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();

    packageItem * item = static_cast<packageItem *>(index.internalPointer());

    if ( role == Qt::CheckStateRole && index.column() == 0 )
        return static_cast<int>( item->isChecked() ? Qt::Checked : Qt::Unchecked );

    if (role == Qt::DecorationRole && index.column() == 0)
        return item->isFavourite() ? QVariant(QIcon(":/Icons/favori")) : QVariant(
                   QIcon(":/Icons/noFavourite"));

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}

Qt::ItemFlags packageModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if ( index.column() == 0 )
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}

QVariant packageModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem_->data(section);

    return QVariant();
}

QModelIndex packageModel::index(int row, int column, const QModelIndex & parent)
const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    packageItem * parentItem;

    if (!parent.isValid())
        parentItem = rootItem_;
    else
        parentItem = static_cast<packageItem *>(parent.internalPointer());

    packageItem * childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex packageModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
        return QModelIndex();

    packageItem * childItem = static_cast<packageItem *>(index.internalPointer());
    packageItem * parentItem = childItem->parent();

    if (parentItem == rootItem_)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int packageModel::rowCount(const QModelIndex & parent) const
{
    packageItem * parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem_;
    else
        parentItem = static_cast<packageItem *>(parent.internalPointer());

    return parentItem->childCount();
}


void packageModel::setupModelData(const QList<QMap<QString, QString>> &
                                  maps, packageItem * parent)
{
    QList<packageItem *> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    for (QMap<QString, QString> map : maps)
    {

        bool isFavorite {map["favorite"] == "1"};
        QList<QVariant> data;
        data.push_back(map.value("name"));
        data.push_back(map.value("version"));
        parents.last()->appendChild(new packageItem(data, isFavorite,
                                    parents.last()));
    }

}

bool packageModel::setData(const QModelIndex & index, const QVariant & value,
                           int role)
{
    packageItem * item = static_cast<packageItem *>(index.internalPointer());

    item->setChecked(item->isChecked() ? false : true);

    return true;
}

void packageModel::selectAllNone(bool isAll)
{
    int i = 0;
    for (; i < rowCount(); ++i)
    {
        packageItem * item = static_cast<packageItem *>(index(i, 0).internalPointer());
        item->setChecked(isAll ? true : false);
    }
    dataChanged(index(0, 0), index(i, 0));
}
