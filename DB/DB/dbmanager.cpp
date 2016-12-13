#include "dbmanager.h"
#include <QtSql>
#include <QDir>
#include <QSqlQuery>
#include <QDebug>

namespace qbrew
{

bool connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("QBrewDB.sqlite");
    db.setUserName("root");
    db.setPassword("rootroot");
    return db.open();
}

void close()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
    {
        db.close();
    }

}

void createTable()
{

    QSqlDatabase db = QSqlDatabase::database();
    if (db.tables().isEmpty())
    {
        QSqlQuery query;
        query.exec("CREATE TABLE FORMULA"
                   "(NAME TEXT NOT NULL PRIMARY KEY,"
                   "VERSION TEXT NOT NULL,"
                   "URL TEXT NOT NULL,"
                   "HOMEPAGE TEXT NOT NULL,"
                   "DESC TEXT NOT NULL)");
    }

}

void deleteTable()
{
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS FORMULA");
}

}
