#include "qbrewdb.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

namespace qbrew
{

QList<PackageDTO> getList(QSqlQuery query)
{
    QList<PackageDTO> list;
    while (query.next())
    {
        bool isInstalled = (query.value(6).toInt() == 1);
        bool isFavorite = (query.value(7).toInt() == 1);
        PackageDTO package {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isInstalled, isFavorite};
        list.push_back(package);
    }
    return list;
}

QList<PackageDTO> getAll()
{
    return getList(QSqlQuery("SELECT * FROM PACKAGES"));
}


QList<PackageDTO> getFavorite()
{
    return getList(QSqlQuery("SELECT * FROM PACKAGES WHERE FAVORITE = 1"));
}

QList<PackageDTO> getInstalled()
{
    return getList(QSqlQuery("SELECT * FROM PACKAGES WHERE INSTALL = 1"));
}

QList<PackageDTO> getSearch (QString searchValue)
{
    QString sql = "SELECT * FROM PACKAGES WHERE "
                  "FILENAME LIKE '%" + searchValue + "%'" +
                  "OR NAME LIKE + '%" + searchValue + "%'";
    QSqlQuery query(sql);
    QList<PackageDTO> list =  getList(query);
    return list;
}


PackageDTO selectPackage(QString filename)
{
    PackageDTO result{};
    QSqlQuery query("SELECT * FROM PACKAGES WHERE NAME = :filename");
    query.bindValue(":filename", filename);
    if (query.next())
    {
        bool isInstalled = (query.value(5).toInt() == 1);
        bool isFavorite = (query.value(6).toInt() == 1);
        PackageDTO PACKAGE {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isInstalled, isFavorite};
        result = PACKAGE;
    }
    return result;
}

bool addPackage(PackageDTO package)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PACKAGES VALUES (:filename, :name, :version, :url, :homepage, :desc, :install, :fav)");
    query.bindValue(":filename", package.filename());
    query.bindValue(":name", package.name());
    query.bindValue(":name", package.name());
    query.bindValue(":version", package.version());
    query.bindValue(":url", package.url());
    query.bindValue(":homepage", package.homepage());
    query.bindValue(":desc", package.desc());
    query.bindValue(":install", package.isInstalled() ? 1 : 0);
    query.bindValue(":fav", package.isFavorite() ? 1 : 0);
    return query.exec();
}

void updateFavorite(PackageDTO package)
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES SET FAVORITE = :favorite WHERE FILENAME = :filename");
    query.bindValue(":filename", package.filename());
    query.bindValue(":favorite", package.isFavorite() ? 1 : 0);
    query.exec();
}

void deletePackage(QString filename)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PACKAGES WHERE FILENAME = :filename");
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
    query.prepare("UPDATE PACKAGES SET INSTALL = 1 WHERE FILENAME = :filename");
    query.bindValue(":filename", filename);
    query.exec();
}

void removeInstalled()
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES SET INSTALL = 0 WHERE INSTALL = 1");
    query.exec();
}

}
