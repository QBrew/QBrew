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
                            query.value(4).toString(), query.value(5).toString(),
                            isInstalled, isFavorite};
        list.push_back(formula);
    }
    return list;
}


QList<FormulaDTO> getFavorite()
{
    QList<FormulaDTO> list;
    QSqlQuery query("SELECT * FROM FORMULA WHERE FAVORITE = 1");
    while (query.next())
    {
        bool isInstalled = (query.value(5).toInt() == 1);
        bool isFavorite = (query.value(6).toInt() == 1);
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isInstalled, isFavorite};
        list.push_back(formula);
    }
    return list;
}

QList<FormulaDTO> getInstalled()
{
    QList<FormulaDTO> list;
    QSqlQuery query("SELECT * FROM FORMULA WHERE INSTALL = 1");
    while (query.next())
    {
        bool isInstalled = (query.value(5).toInt() == 1);
        bool isFavorite = (query.value(6).toInt() == 1);
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isInstalled, isFavorite};
        list.push_back(formula);
    }
    return list;
}


FormulaDTO selectFormula(QString filename)
{
    FormulaDTO result{};
    QSqlQuery query("SELECT * FROM FORMULA WHERE NAME = :filename");
    query.bindValue(":filename", filename);
    if (query.next())
    {
        bool isInstalled = (query.value(5).toInt() == 1);
        bool isFavorite = (query.value(6).toInt() == 1);
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isInstalled, isFavorite};
        result = formula;
    }
    return result;
}

bool addFormula(FormulaDTO formula)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMULA VALUES (:filename, :name, :version, :url, :homepage, :desc, :install, :fav)");
    query.bindValue(":filename", formula.filename());
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

void deleteFormula(QString filename)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FORMULA WHERE FILENAME = :filename");
    query.bindValue(0, filename);
    query.exec();
}
}
