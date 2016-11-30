#include "dbmanager.h"
#include <QtSql>

namespace qbrew
{

bool connection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("QBrewDB");
    db.setUserName("root");
    db.setPassword("rootroot");
    return db.open();
}

bool close()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
    {
        db.close();
    }
}

}
