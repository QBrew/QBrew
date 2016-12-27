#ifndef QBREWDB_H
#define QBREWDB_H

#include <QList>
#include "../dto/packagedto.h"

namespace qbrew
{
QList<PackageDTO> getAll();
QList<PackageDTO> getFavorite();
QList<PackageDTO> getInstalled();
QList<PackageDTO> getSearch(QString searchValue);

PackageDTO selectPackage(QString filename);
bool addPackage(PackageDTO package);
void addFavorite(PackageDTO package);
void deletePackage(QString filename);
void updateInstalled(QStringList filenames);
void addInstalled(QString filename);
void removeInstalled();
}

#endif // QBREWDB_H
