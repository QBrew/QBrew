#ifndef QBREWDB_H
#define QBREWDB_H

#include <QList>
#include "../DTO/formuladto.h"

namespace qbrew
{
QList<FormulaDTO> getAll();
FormulaDTO selectFormula(QString name);
bool addFormula(FormulaDTO formula);
void updateFormula(FormulaDTO formula);
void deleteFormula(QString name);
}

#endif // QBREWDB_H
