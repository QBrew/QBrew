#ifndef QBREWDB_H
#define QBREWDB_H

#include <QList>
#include "../dto/packagedto.h"

namespace qbrew
{
QList<PackageDTO> getAll();
QList<PackageDTO> getFavourite();
QList<PackageDTO> getInstalled();
QList<PackageDTO> getSearch(QString searchValue);

PackageDTO selectPackage(QString filename);
bool addPackage(PackageDTO package);
void updateFavourite(PackageDTO package);
void deletePackage(QString filename);
void addListInstalled(QStringList filenames);
void addInstalled(QString filename);
void removeAllInstalled();
}

#endif // QBREWDB_H
