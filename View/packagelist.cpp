#include "packagelist.h"

#include <QHeaderView>

void packageList::setHeaderLabels()
{
    QStringList headerLabels
    {
        tr(""),
        tr(""),
        tr("Name"),
        tr("Version")
    };

    QStandardItemModel * model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(headerLabels);

    setModel(model);

    setSortingEnabled(true);
    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void packageList::setTreeView()
{
    QStandardItemModel * model = new QStandardItemModel();

    QStandardItem * check;
    QStandardItem * favori;
    QStandardItem * name;
    QStandardItem * version;

    for (std::string test : qbrew::list(false))
    {

        check = new QStandardItem();
        favori = new QStandardItem();
        name = new QStandardItem(QString::fromStdString(test));
        version = new QStandardItem(QString::fromStdString(
                                        qbrew::infoPackage(test,
                                                false).at("version")));

        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        version->setFlags(version->flags() & ~Qt::ItemIsEditable);

        model->appendRow(QList<QStandardItem *>() << check << favori << name <<
                         version);
    }

    model->setHorizontalHeaderItem(0, new QStandardItem());
    model->setHorizontalHeaderItem(1, new QStandardItem());
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Version")));

    header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setAlternatingRowColors(true);
    setModel(model);
}

packageList::packageList(QWidget * parent) : QTreeView(parent)
{
    setHeaderLabels();

    setTreeView();
}

/*QVariant packageList::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();

    packageList * item = static_cast<packageList *>(index.internalPointer());

    if ( role == Qt::CheckStateRole && index.column() == 0 )
        return static_cast<int>( item->isChecked() ? Qt::Checked : Qt::Unchecked );

    if (role != Qt::DisplayRole)
        return QVariant();

    return item->data(index.column());
}*/

Qt::ItemFlags packageList::flags(const QModelIndex & index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if ( index.column() == 0 )
        flags |= Qt::ItemIsUserCheckable;

    return flags;
}
