#ifndef QBREWDB_H
#define QBREWDB_H

#include <QList>
#include "../DTO/formuladto.h"

namespace qbrew
{
QList<FormulaDTO> getAll();
QList<FormulaDTO> getFavorite();
QList<FormulaDTO> getInstalled();

FormulaDTO selectFormula(QString filename);
bool addFormula(FormulaDTO formula);
void updateFormula(FormulaDTO formula);
void deleteFormula(QString filename);
}

#endif // QBREWDB_H
