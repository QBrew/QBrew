#include "favoritedb.h"
#include <QtSql>
#include <iostream>
#include <QDebug>

namespace qbrew
{

void createTableFavorite()
{
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS FAVORITE");
    query.exec("CREATE TABLE FAVORITE"
               " (NAME    TEXT NOT NULL PRIMARY KEY)");
}

QList<QString> getAllFavorite()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM FAVORITE");
    query.exec();
    QList<QString> favorites;
    while (query.next())
    {
        favorites.push_back(query.value(0).toString());
    }
    return favorites;
}

bool addToFavorite(QString fav)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FAVORITE VALUES (:name)");
    query.bindValue(0, fav);
    return query.exec();

}

bool removeFromFavorite(QString fav)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FAVORITE WHERE NAME = :name");
    query.bindValue(0, fav);
    return query.exec();
}

}
