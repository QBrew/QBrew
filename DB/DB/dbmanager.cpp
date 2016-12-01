#include "dbmanager.h"
#include <QtSql>

namespace qbrew
{

bool connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("favorite.qbrew");
    db.setUserName("root");
    db.setPassword("root");
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

}
