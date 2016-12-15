#include "packagelist.h"
#include "packagemodel.h"
#include "../Process/process.h"

#include <QHeaderView>
#include <QFile>
#include <QFileInfoList>

using namespace qbrew;

void PackageList::setTreeView()
{
    PackageModel * model = new PackageModel();

    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    setAlternatingRowColors(true);
    setModel(model);
}

PackageList::PackageList(QWidget * parent) : QTreeView(parent)
{
    setTreeView();
}
