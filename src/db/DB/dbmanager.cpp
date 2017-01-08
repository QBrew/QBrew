#include "dbmanager.h"
#include <QtSql>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "../../process/process.h"

namespace qbrewdb
{

bool connection()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
            QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
            db.setDatabaseName(QDir::homePath() + "/.QBrewDB");
            return db.open();
    }
    return false;
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
        query.exec("CREATE TABLE PACKAGES ("
                   "FILENAME    TEXT    NOT NULL,"
                   "NAME        TEXT    NOT NULL,"
                   "VERSION     TEXT    NOT NULL,"
                   "HOMEPAGE    TEXT    NOT NULL,"
                   "URL         TEXT    NOT NULL,"
                   "DESC        TEXT    NOT NULL,"
                   "CASK        INT     NOT NULL,"
                   "INSTALL     INT     NOT NULL,"
                   "FAVOURITE   INT     NOT NULL,"
                   "PRIMARY KEY (FILENAME, CASK)"
                   ")");
    }

}

void dropTable()
{
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS PACKAGES");
}

void initialize()
{
    connection();
    dropTable();

    QSqlDatabase db = QSqlDatabase::database();
    if (db.tables().isEmpty())
    {
        createTable();
        qbrewprocess::createDB(true); //db for brew cask
        qbrewprocess::createDB(false); //db for brew
    }

    removeAllInstalled();
    addListInstalled(qbrewprocess::list(true), true);
    addListInstalled(qbrewprocess::list(false), false);
}

}
