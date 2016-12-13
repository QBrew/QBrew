#include "packagelist.h"
#include "packagemodel.h"
#include "Process/process.h"

#include <QHeaderView>
#include <QFile>
#include <QDebug>

#include <QFileInfoList>

using namespace qbrew;

void packageList::setTreeView()
{
    QList<QMap<QString, QString>> maps;
    for (auto package : search(QString(""), true))
    {
        QMap<QString, QString> map = infoPackage(package.baseName(), true);
        maps.append(map);
    }

    packageModel * model = new packageModel(maps);

    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    setAlternatingRowColors(true);
    setModel(model);
}

packageList::packageList(QWidget * parent) : QTreeView(parent)
{
    setTreeView();
}
