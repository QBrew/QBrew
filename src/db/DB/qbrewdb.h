#ifndef QBREWDB_H
#define QBREWDB_H

#include <QList>
#include "../dto/packagedto.h"

namespace qbrew
{
QList<PackageDTO> getAll();
QList<PackageDTO> getFavourites();
QList<PackageDTO> getInstalled();
QList<PackageDTO> getSearch(QString searchValue);

PackageDTO selectPackage(QString filename, bool isCask);
bool addPackage(PackageDTO package);
void addFavourite(QString filename, bool isCask);

void updateFavourite(PackageDTO package);
void deletePackage(QString filename, bool isCask);

void addListInstalled(QStringList filenames, bool isCask);
void addInstalled(PackageDTO package);
void addInstalled(QString filename, bool isCask);

void removeInstalled(PackageDTO package);
void removeInstalled(QString filename, bool isCask);

void removeAllInstalled();
void removeAllFavourites();
}

#endif // QBREWDB_H
