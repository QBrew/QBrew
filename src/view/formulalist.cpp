#include "formulalist.h"
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>

#include <src/db/DB/qbrewdb.h>
#include <src/db/DTO/formuladto.h>


FormulaList::FormulaList(QWidget * parent)
{
    QStringList qsl;
    qsl << "" << "Filename" << "Name" << "Version" << "Favorite" << "Installed";
    this->setColumnCount(qsl.size());
    this->setHorizontalHeaderLabels(qsl);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->verticalHeader()->setVisible(false);
    this->setAlternatingRowColors(true);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(MultiSelection);

    this->setColumnWidth(0, 50);
    this->setColumnWidth(1, 500);
    this->horizontalHeader()->setStretchLastSection(true);

    this->setAll();

}

void FormulaList::setAll()
{
    setList(qbrew::getAll());
}

void FormulaList::setFavorite()
{
    setList(qbrew::getFavorite());
}

void FormulaList::setInstalled()
{
    setList(qbrew::getInstalled());
}

void FormulaList::selectFormula(bool isAll)
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

void FormulaList::setList(const QList<qbrew::FormulaDTO> & list)
{
    this->setRowCount(list.size());
    int i {0};
    for (qbrew::FormulaDTO f : list)
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

        QCheckBox * isFavorite = new QCheckBox();
        isInstalled->setChecked(f.isFavorite());
        isFavorite->setCheckable(false);
        this->setCellWidget(i, j++, isFavorite);

        QCheckBox * isInstalled = new QCheckBox();
        isInstalled->setChecked(f.isInstalled());
        isInstalled->setCheckable(false);
        this->setItem(i, j++, isInstalled);

        i++;
    }
}


void FormulaList::tableItemClicked(int row, int column)
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

void FormulaList::tableItemDoubleClicked(int row, int column)
{
    QCheckBox * checkBox = checkBoxes_.at(row);
    checkBox->setChecked(!checkBox->isChecked());
}
