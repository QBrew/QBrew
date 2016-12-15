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
        bool isInstalled = (query.value(5).toInt() == 1);
        bool isFavorite = (query.value(6).toInt() == 1);
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), isInstalled, isFavorite};
        list.push_back(formula);
    }
    return list;
}

FormulaDTO selectFormula(QString name)
{
    FormulaDTO result{};
    QSqlQuery query("SELECT * FROM FORMULA WHERE NAME = :name");
    query.bindValue(":name", name);
    if (query.next())
    {
        bool isInstalled = (query.value(5).toInt() == 1);
        bool isFavorite = (query.value(6).toInt() == 1);
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), isInstalled, isFavorite};
        result = formula;
    }
    return result;
}

bool addFormula(FormulaDTO formula)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMULA VALUES (:name, :version, :url, :homepage, :desc, :install, :fav)");
    query.bindValue(":name", formula.name());
    query.bindValue(":name", formula.name());
    query.bindValue(":version", formula.version());
    query.bindValue(":url", formula.url());
    query.bindValue(":homepage", formula.homepage());
    query.bindValue(":desc", formula.desc());
    query.bindValue(":install", formula.isInstalled() ? 1 : 0);
    query.bindValue(":fav", formula.isFavorite() ? 1 : 0);
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
