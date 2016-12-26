#include "formulalist.h"
#include <QHeaderView>
#include <QCheckBox>
#include <QHBoxLayout>

#include <src/db/DB/qbrewdb.h>
#include <src/db/DTO/formuladto.h>


FormulaList::FormulaList(QWidget * parent)
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
    this->setColumnWidth(1, 500);
    this->horizontalHeader()->setStretchLastSection(true);

    this->setFavorite();

}

void FormulaList::setAll()
{
    formula_ = qbrew::getAll();
    setList();
}

void FormulaList::setFavorite()
{
    formula_ = qbrew::getFavorite();
    setList();
}

void FormulaList::setInstalled()
{
    formula_ = qbrew::getFavorite();
    setList();
}

void FormulaList::search(QString searchValue)
{
    formula_ = qbrew::getSearch(searchValue);
    setList();
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

QList<qbrew::FormulaDTO> FormulaList::getSelected()
{
    QList<qbrew::FormulaDTO> result;
    int i{0};
    for (QCheckBox * checkBox : checkBoxes_)
    {
        if (checkBox->isChecked())
        {
            result.append(formula_.at(i));
        }
        i++;
    }
    return result;
}

void FormulaList::setList()
{
    checkBoxes_.clear();
    this->setRowCount(formula_.size());
    int i {0};
    for (qbrew::FormulaDTO f : formula_)
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
