#include "packagelist.h"
#include "packagemodel.h"
#include "Process/process.h"

#include <QHeaderView>
#include <QFile>
#include <QFileInfoList>

using namespace qbrew;

void packageList::setTreeView()
{
    packageModel * model = new packageModel();

    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    setAlternatingRowColors(true);
    setModel(model);
}

packageList::packageList(QWidget * parent) : QTreeView(parent)
{
    setTreeView();
}
