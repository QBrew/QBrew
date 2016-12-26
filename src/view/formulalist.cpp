#include "formulalist.h"
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>

#include <src/db/DB/qbrewdb.h>
#include <src/db/DTO/formuladto.h>


FormulaList::FormulaList(QWidget * parent)
{
    QStringList qsl;
    qsl << "" << "Name" << "Version";
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
    QList<qbrew::FormulaDTO> list;
    list = qbrew::getAll();
    setList(list);
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
        QCheckBox * checkBox = new QCheckBox();
        checkBox->setChecked(false);
        checkBoxes_.append(checkBox);
        this->setCellWidget(i, 0, checkBox);

        QTableWidgetItem * name = new QTableWidgetItem(f.name());
        name->setFlags(name->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, 1, name);

        QTableWidgetItem * version = new QTableWidgetItem(f.version());
        version->setFlags(version->flags() ^ Qt::ItemIsEditable);
        this->setItem(i, 2, version);
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
