#ifndef QBREWDB_H
#define QBREWDB_H

#include <QList>
#include "../DTO/formuladto.h"

namespace qbrew
{
QList<FormulaDTO> getAll();
QList<FormulaDTO> getFavorite();
QList<FormulaDTO> getInstalled();
QList<FormulaDTO> getSearch(QString searchValue);

FormulaDTO selectFormula(QString filename);
bool addFormula(FormulaDTO formula);
void addFavorite(FormulaDTO formula);
void deleteFormula(QString filename);
void updateInstalled(QStringList filenames);
void addInstalled(QString filename);
void removeInstalled();
}

#endif // QBREWDB_H
