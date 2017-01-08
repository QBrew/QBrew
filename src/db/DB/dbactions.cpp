#include "dbactions.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

namespace qbrewdb
{

QList<PackageDTO> getList(QSqlQuery query)
{
    QList<PackageDTO> list;
    while (query.next())
    {
        bool isCask = (query.value(6).toInt() == 1);
        bool isInstalled = (query.value(7).toInt() == 1);
        bool isFavourite = (query.value(8).toInt() == 1);
        PackageDTO package {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isCask, isInstalled, isFavourite};
        list.push_back(package);
    }
    return list;
}

QList<PackageDTO> getFavourites()
{
    return getList(QSqlQuery("SELECT * FROM PACKAGES "
                             "WHERE FAVOURITE = 1 "
                             "ORDER BY FILENAME"));
}

QList<PackageDTO> getInstalled()
{
    return getList(QSqlQuery("SELECT * FROM PACKAGES "
                             "WHERE INSTALL = 1 "
                             "ORDER BY FILENAME"));
}

QList<PackageDTO> getSearch (QString searchValue)
{
    QString sql = "SELECT * FROM PACKAGES WHERE "
                  "FILENAME LIKE '%" + searchValue + "%'" +
                  "OR NAME LIKE + '%" + searchValue + "%'" +
                  "ORDER BY FILENAME";
    QSqlQuery query(sql);
    QList<PackageDTO> list =  getList(query);
    return list;
}


PackageDTO selectPackage(QString filename, bool isCask)
{
    PackageDTO result{};
    QSqlQuery query("SELECT * FROM PACKAGES "
                    "WHERE NAME = :filename "
                    "AND CASK = :cask");
    query.bindValue(":filename", filename);
    query.bindValue(":cask", isCask ? 1 : 0);
    if (query.next())
    {
        bool isCask = (query.value(6).toInt() == 1);
        bool isInstalled = (query.value(7).toInt() == 1);
        bool isFavourite = (query.value(8).toInt() == 1);
        PackageDTO PACKAGE {query.value(0).toString(), query.value(1).toString(),
                            query.value(2).toString(), query.value(3).toString(),
                            query.value(4).toString(), query.value(5).toString(),
                            isCask, isInstalled, isFavourite};
        result = PACKAGE;
    }
    return result;
}

bool addPackage(PackageDTO package)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PACKAGES VALUES (:filename, :name, :version, "
                  " :url, :homepage, :desc, :cask, :install, :fav)");
    query.bindValue(":filename", package.filename());
    query.bindValue(":name", package.name());
    query.bindValue(":name", package.name());
    query.bindValue(":version", package.version());
    query.bindValue(":url", package.url());
    query.bindValue(":homepage", package.homepage());
    query.bindValue(":desc", package.desc());
    query.bindValue(":cask", package.isCask() ? 1 : 0);
    query.bindValue(":install", package.isInstalled() ? 1 : 0);
    query.bindValue(":fav", package.isFavourite() ? 1 : 0);
    return query.exec();
}

void addFavourite(QString filename, bool isCask)
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES SET FAVOURITE = 1 "
                  "WHERE FILENAME = :filename "
                  "AND CASK = :cask");
    query.bindValue(":filename", filename);
    query.bindValue(":cask", isCask ? 1 : 0);
    query.exec();
}

void updateFavourite(PackageDTO package)
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES SET FAVOURITE = :favourite "
                  "WHERE FILENAME = :filename "
                  "AND CASK = :cask");
    query.bindValue(":filename", package.filename());
    query.bindValue(":favourite", package.isFavourite() ? 1 : 0);
    query.bindValue(":cask", package.isCask() ? 1 : 0);
    query.exec();
}

void deletePackage(QString filename, bool isCask)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PACKAGES WHERE "
                  "FILENAME = :filename "
                  "AND CASK = :cask");
    query.bindValue(":filename", filename);
    query.bindValue(":cask", isCask ? 1 : 0);
    query.exec();
}


void addListInstalled(QStringList filenames, bool isCask)
{
    for (QString filename : filenames)
    {
        addInstalled(filename, isCask);
    }
}


void addInstalled(PackageDTO package)
{
    addInstalled(package.filename(), package.isCask());
}

void addInstalled(QString filename, bool isCask)
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES SET INSTALL = 1 "
                  "WHERE FILENAME = :filename "
                  "AND CASK = :cask");
    query.bindValue(":filename", filename);
    query.bindValue(":cask", isCask ? 1 : 0);
    query.exec();
}

void removeInstalled(PackageDTO package)
{
    removeInstalled(package.filename(), package.isCask());
}


void removeInstalled(QString filename, bool isCask)
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES SET INSTALL = 0 "
                  "WHERE FILENAME = :filename "
                  "AND CASK = :cask");
    query.bindValue(":filename", filename);
    query.bindValue(":cask", isCask ? 1 : 0);
    query.exec();
}

void removeAllInstalled()
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES "
                  "SET INSTALL = 0 "
                  "WHERE INSTALL = 1");
    query.exec();
}

void removeAllFavourites()
{
    QSqlQuery query;
    query.prepare("UPDATE PACKAGES "
                  "SET FAVOURITE = 0 "
                  "WHERE FAVOURITE = 1");
    query.exec();
}

}
