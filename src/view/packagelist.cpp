#include "packagelist.h"
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>

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

    this->setInstalled();
}

void PackageList::setAll()
{
    packages_ = qbrew::getAll();
    setList();
}

void PackageList::setFavorite()
{
    packages_ = qbrew::getFavorite();
    setList();
}

void PackageList::setInstalled()
{
    packages_ = qbrew::getInstalled();
    setList();
}

void PackageList::search(QString searchValue)
{
    packages_ = qbrew::getSearch(searchValue);
    setList();
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

QList<qbrew::PackageDTO> PackageList::getSelectedFavorite()
{
    QList<qbrew::PackageDTO> result;
    int i{0};
    for (QCheckBox * checkBox : checkBoxes_)
    {
        if (checkBox->isChecked())
        {
            qbrew::PackageDTO f = packages_.at(i);
            f.setIsFavorite(true);
            result.append(f);
        }
        i++;
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
        this->setCellWidget(i, j++, checkBox);

        QTableWidgetItem * filename = new QTableWidgetItem(f.filename());
        filename->setFlags(filename->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, filename);

        QTableWidgetItem * name = new QTableWidgetItem(f.name());
        name->setFlags(name->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, name);

        QTableWidgetItem * version = new QTableWidgetItem(f.version());
        version->setFlags(version->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, j++, version);

        QCheckBox * isInstalled = new QCheckBox();
        isInstalled->setChecked(f.isInstalled());
        isInstalled->setAttribute(Qt::WA_TransparentForMouseEvents);
        isInstalled->setFocusPolicy(Qt::NoFocus);
        this->setCellWidget(i, j++, isInstalled);

        QCheckBox * isFavorite = new QCheckBox();
        isFavorite->setChecked(f.isFavorite());
        isFavorite->setAttribute(Qt::WA_TransparentForMouseEvents);
        isFavorite->setFocusPolicy(Qt::NoFocus);
        this->setCellWidget(i, j++, isFavorite);

        i++;
    }
}


void PackageList::tableItemClicked(int row, int column)
{
    this->clearSelection();
    int i {0};
    for (QCheckBox * checkBox : checkBoxes_)
    {
        if (checkBox->isChecked())
        {
            this->selectRow(i);
        }
        i++;
    }
    if (!checkBoxes_.at(row)->isChecked())
    {
        this->selectRow(row);
    }
}

void PackageList::tableItemDoubleClicked(int row, int column)
{
    QCheckBox * checkBox = checkBoxes_.at(row);
    checkBox->setChecked(!checkBox->isChecked());
}
