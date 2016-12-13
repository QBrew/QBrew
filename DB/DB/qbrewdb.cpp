#include "qbrewdb.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

namespace qbrew
{

QList<FormulaDTO> getAll()
{
    QList<FormulaDTO> list;
    QSqlQuery query("SELECT * FROM FORMULA");
    while (query.next())
    {
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString()};
        list.push_back(formula);
    }
    return list;
}

FormulaDTO selectFormula(QString name)
{
    FormulaDTO result {name};
    QSqlQuery query("SELECT * FROM FORMULA WHERE NAME = :name");
    query.bindValue(":name", name);
    if (query.next())
    {
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString()};
        result = formula;
    }
    return result;
}

bool addFormula(FormulaDTO formula)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMULA VALUES (:name, :version, :url, :homepage, :desc)");
    query.bindValue(":name", formula.name());
    query.bindValue(":name", formula.name());
    query.bindValue(":version", formula.version());
    query.bindValue(":url", formula.url());
    query.bindValue(":homepage", formula.homepage());
    query.bindValue(":desc", formula.desc());
    return query.exec();
}

void updateFormula(FormulaDTO formula)
{

}

void deleteFormula(QString name)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FORMULA WHERE NAME = :name");
    query.bindValue(0, name);
    query.exec();
}

}
