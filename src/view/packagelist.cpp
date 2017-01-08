#include "packagelist.h"

#include "../db/db/dbactions.h"
#include "../db/dto/packagedto.h"

#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>

namespace qbrewview
{

QString PackageList::getStatus() const
{
    return status_;
}

bool PackageList::getCheck(int row) const
{
    return checkBoxes_.at(row)->isChecked();
}

PackageList::PackageList(QWidget * parent) : QTableWidget(parent)
{
    QStringList qsl;
    qsl << "" << "Filename" << "Cask" << "Name" << "Version"
        << "Installed" << "Favourite";
    this->setColumnCount(qsl.size());
    this->setHorizontalHeaderLabels(qsl);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->verticalHeader()->setVisible(false);
    this->setAlternatingRowColors(true);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(MultiSelection);

    int i = 0;
    this->setColumnWidth(i++, 30);      //check
    this->setColumnWidth(i++, 300);     //filename
    this->setColumnWidth(i++, 60);      //cask
    this->setColumnWidth(i++, 300);     //name
    this->setColumnWidth(i++, 300);     //version
    this->setColumnWidth(i++, 60);      //installed
    this->horizontalHeader()->setStretchLastSection(true);

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setInstalled();

    row_ = -1;
    status_ = "Installed";
}

void PackageList::setFavourite()
{
    packages_ = getFavourites();
    setList();
    status_ = "Favourite";
}

void PackageList::setInstalled()
{
    packages_ = getInstalled();
    setList();
    status_ = "Installed";
}

void PackageList::setSearch(QString searchValue)
{
    packages_ = getSearch(searchValue);
    setList();
    status_ = searchValue;
}

void PackageList::update()
{
    int row = row_;
    QString filename;
    if (row != -1)
    {
        filename = packages_.at(row_).filename();
    }
    if (status_ == "Favourite")
    {
        setFavourite();
    }
    else
    {
        if (status_ == "Installed")
        {
            setInstalled();
        }
        else
        {
            setSearch(status_);
        }
    }
    if (row != -1 && row < packages_.size()
            && filename == packages_.at(row).filename())
    {
        row_ = row;
        selectRow(row_);
    }
}

PackageDTO PackageList::selected()
{
    return packages_.at(row_);
}

PackageDTO PackageList::getPackage(int row)
{
    return packages_.at(row);
}

void PackageList::setSelectPackage(bool isAll)
{
    for (QCheckBox * checkBox : checkBoxes_)
    {
        checkBox->setChecked(isAll);
    }
}

QList<PackageDTO> PackageList::listSelected()
{
    QList<PackageDTO> result;
    int i{0};
    for (QCheckBox * checkBox : checkBoxes_)
    {
        if (checkBox->isChecked())
        {
            PackageDTO f = packages_.at(i);
            result.append(f);
        }
        i++;
    }
    return result;
}

void PackageList::setList()
{

    QList<QIcon> statusIcons;
    statusIcons << QIcon(":/Icons/favourite")
                << QIcon(":/Icons/noFavourite")
                << QIcon(":/Icons/selectAll")
                << QIcon(":/Icons/selectNone");
    checkBoxes_.clear();
    this->setRowCount(packages_.size());
    int i {0};
    for (PackageDTO f : packages_)
    {
        int j {0};
        QCheckBox * checkBox = new QCheckBox();
        checkBox->setChecked(false);
        checkBoxes_.append(checkBox);
        this->setCellWidget(i, j++, alignCheckBox(checkBox));

        QTableWidgetItem * filename = new QTableWidgetItem(f.filename());
        filename->setFlags(filename->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, filename);

        QTableWidgetItem * caskIcon = new QTableWidgetItem;
        caskIcon->setIcon(f.isCask() ? statusIcons.at(2) : statusIcons.at(3));
        this->setItem(i, j++, caskIcon);

        QTableWidgetItem * name = new QTableWidgetItem(f.name());
        name->setFlags(name->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, name);

        QTableWidgetItem * version = new QTableWidgetItem(f.version());
        version->setFlags(version->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, version);

        QTableWidgetItem * installedIcon = new QTableWidgetItem;
        installedIcon->setIcon(f.isInstalled() ?
                               statusIcons.at(2) : statusIcons.at(3));
        this->setItem(i, j++, installedIcon);

        QTableWidgetItem * favouriteIcon = new QTableWidgetItem;
        favouriteIcon->setIcon(f.isFavourite() ?
                               statusIcons.at(0) : statusIcons.at(1));
        this->setItem(i, j++, favouriteIcon);

        i++;
    }
    this->clearSelection();
    row_ = -1;
}

QWidget * PackageList::alignCheckBox(QCheckBox * cb)
{
    QWidget * widget = new QWidget();
    QHBoxLayout * layout = new QHBoxLayout(widget);
    layout->addWidget(cb);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);
    return widget;
}

void PackageList::tableItemClicked(int row)
{
    this->clearSelection();
    this->selectRow(row);
    if (row_ != row)
    {
        row_ = row;
        emit clickedItemChange();
    }
}

void PackageList::tableItemDoubleClicked(int row)
{
    QCheckBox * checkBox = checkBoxes_.at(row);
    checkBox->setChecked(!checkBox->isChecked());
}

}
