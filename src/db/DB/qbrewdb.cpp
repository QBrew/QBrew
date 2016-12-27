#include "qbrewdb.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

namespace qbrew
{

QList<FormulaDTO> getList(QSqlQuery query)
{
    QList<FormulaDTO> list;
    while (query.next())
    {
        bool isInstalled = (query.value(6).toInt() == 1);
        bool isFavorite = (query.value(7).toInt() == 1);
        FormulaDTO formula {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isInstalled, isFavorite};
        list.push_back(formula);
    }
    return list;
}

QList<FormulaDTO> getAll()
{
    return getList(QSqlQuery("SELECT * FROM FORMULA"));
}


QList<FormulaDTO> getFavorite()
{
    return getList(QSqlQuery("SELECT * FROM FORMULA WHERE FAVORITE = 1"));
}

QList<FormulaDTO> getInstalled()
{
    return getList(QSqlQuery("SELECT * FROM FORMULA WHERE INSTALL = 1"));
}

QList<FormulaDTO> getSearch (QString searchValue)
{
    QString sql = "SELECT * FROM FORMULA WHERE "
                  "FILENAME LIKE '%" + searchValue + "%'" +
                  "OR NAME LIKE + '%" + searchValue + "%'";
    QSqlQuery query(sql);
    QList<FormulaDTO> list =  getList(query);
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

void addFavorite(FormulaDTO formula)
{
    QSqlQuery query;
    query.prepare("UPDATE FORMULA SET FAVORITE = 1 WHERE FILENAME = :filename");
    query.bindValue(":filename", formula.filename());
    query.exec();
}

void deleteFormula(QString filename)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FORMULA WHERE FILENAME = :filename");
    query.bindValue(":filename", filename);
    query.exec();
}


void updateInstalled(QStringList filenames)
{
    removeInstalled();
    for (QString filename : filenames)
    {
        addInstalled(filename);
    }
}

void addInstalled(QString filename)
{
    QSqlQuery query;
    query.prepare("UPDATE FORMULA SET INSTALL = 1 WHERE FILENAME = :filename");
    query.bindValue(":filename", filename);
    query.exec();
}

void removeInstalled()
{
    QSqlQuery query;
    query.prepare("UPDATE FORMULA SET INSTALL = 0 WHERE INSTALL = 1");
    query.exec();
}

}
