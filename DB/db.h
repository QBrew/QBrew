#ifndef DB_H
#define DB_H

#include <vector>
#include <QString>
#include <QSqlQuery>

namespace qbrew
{

bool connection();
void createTable();
void insertIntoTable(QString name);
void displayTable();
std::vector<QString> getTable();

}

#endif // DB_H 
