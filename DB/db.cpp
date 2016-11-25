#include "db.h"
#include <QtSql>
#include <QDebug>

#define q2c(string) string.toStdString()

namespace qbrew
{

#include <QCoreApplication>
#include <QtSql>
#include <QDebug>

bool connection()
{
    QString path = "Formula";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (!db.open())
    {
        qDebug() << db.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "DB open sucessfully";
        return true;
    }

}

void createTableFormula()
{
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS FORMULA");
    query.exec("CREATE TABLE FORMULA "
               "(NAME    TEXT NOT NULL PRIMARY KEY,"
               "VERSION TEXT)");
}

void insertIntoTable(QString name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FORMULA (NAME) "
                  "VALUES (:name)");
    query.bindValue(":name", name);
    query.exec();
}

void search(QString name)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMULA WHERE NAME LIKE :name");
    query.bindValue(":name", name);
    query.exec();
    if (query.next())
    {
        QString name = query.value(0).toString();
        qDebug() << name;
    }
    else
    {
        qDebug() << "SqLite error:" << query.lastError().text() <<
                 ", SqLite error code:" << query.lastError().number();
    }
}

std::vector<QString> getTable()
{
    std::vector<QString> names;
    QSqlQuery query;
    query.exec("SELECT * FROM FORMULA");
    while (query.next())
    {
        QString name = query.value(0).toString();
        names.push_back(name);

    }
}

}
