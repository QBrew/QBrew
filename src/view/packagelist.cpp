#include "packagelist.h"
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>

#include <src/db/db/qbrewdb.h>
#include <src/db/dto/packagedto.h>

using namespace qbrew;


PackageList::PackageList(QWidget * parent)
{
    QStringList qsl;
    qsl << "" << "Filename" << "Name" << "Version" << "Installed" << "Favorite";
    this->setColumnCount(qsl.size());
    this->setHorizontalHeaderLabels(qsl);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->verticalHeader()->setVisible(false);
    this->setAlternatingRowColors(true);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(MultiSelection);

    this->setColumnWidth(0, 50);
    this->setColumnWidth(1, 300);
    this->setColumnWidth(2, 300);
    this->horizontalHeader()->setStretchLastSection(true);

    this->setIcons();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setInstalled();

    row_ = -1;
    status = "Installed";
}

void PackageList::setFavorite()
{
    packages_ = qbrew::getFavorite();
    setList();
    status = "Favorite";
}

void PackageList::setInstalled()
{
    packages_ = qbrew::getInstalled();
    setList();
    status = "Installed";
}

void PackageList::setIcons()
{
    statusIcons_ << QIcon(":/Icons/favori") << QIcon(":/Icons/noFavourite") <<
                 QIcon(":/Icons/selectAll") << QIcon(":/Icons/selectNone");
}

void PackageList::setSearch(QString searchValue)
{
    packages_ = qbrew::getSearch(searchValue);
    setList();
    status = searchValue;
}

void PackageList::update()
{
    int row = row_;
    if (status == "Favorite")
    {
        setFavorite();
    }
    else
    {
        if (status == "Installed")
        {
            setInstalled();
        }
        else
        {
            setSearch(status);
        }
    }
    if (row != -1)
    {
        row_ = row;
        selectRow(row_);
    }
}

void PackageList::selectPackage(bool isAll)
{
    if (isAll)
    {
        this->selectAll();
    }
    else
    {
        this->clearSelection();
    }
    for (QCheckBox * checkBox : checkBoxes_)
    {
        checkBox->setChecked(isAll);
    }
}

QList<PackageDTO> PackageList::getSelected()
{
    QList<qbrew::PackageDTO> result;
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
    if (row_ != -1 && !checkBoxes_.at(row_)->isChecked())
    {
        PackageDTO f = packages_.at(row_);
        f.setIsFavorite(true);
        result.append(f);
    }
    return result;
}

void PackageList::setList()
{
    checkBoxes_.clear();
    this->setRowCount(packages_.size());
    int i {0};
    for (qbrew::PackageDTO f : packages_)
    {
        int j {0};
        QCheckBox * checkBox = new QCheckBox();
        checkBox->setChecked(false);
        checkBoxes_.append(checkBox);
        this->setCellWidget(i, j++, alignCheckBox(checkBox));

        QTableWidgetItem * filename = new QTableWidgetItem(f.filename());
        filename->setFlags(filename->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, filename);

        QTableWidgetItem * name = new QTableWidgetItem(f.name());
        name->setFlags(name->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, name);

        QTableWidgetItem * version = new QTableWidgetItem(f.version());
        version->setFlags(version->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, version);

        QTableWidgetItem * installedIcon = new QTableWidgetItem;
        installedIcon->setIcon(f.isInstalled() ? statusIcons_.at(2) : statusIcons_.at(
                                   3));
        this->setItem(i, j++, installedIcon);

        QTableWidgetItem * favoriteIcon = new QTableWidgetItem;
        favoriteIcon->setIcon(f.isFavorite() ? statusIcons_.at(0) : statusIcons_.at(1));
        this->setItem(i, j++, favoriteIcon);

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


void PackageList::tableItemClicked(int row, int column)
{
    this->clearSelection();
    this->selectRow(row);
    if (row_ != row)
    {
        //send signal;
        row_ = row;
    }
}

void PackageList::tableItemDoubleClicked(int row, int column)
{
    QCheckBox * checkBox = checkBoxes_.at(row);
    checkBox->setChecked(!checkBox->isChecked());
}
