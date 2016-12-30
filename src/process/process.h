#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <QMap>
#include <QFileInfoList>
#include "../db/db/qbrewdb.h"

namespace qbrew
{

bool isBrewCaskInstalled();
QString getBrewPath(bool cask);

QPair<QString, QString> brewVersion();

void createDB(bool cask);

int install(PackageDTO package);
int uninstall(PackageDTO package);

QStringList list(bool isCask);
QStringList listArgument(QString argument);

QMap<QString, QString> infoPackage(QString filename, bool cask);
void addToMap(QMap<QString, QString> & map, QStringList & infos, QString line);

void cleanup(bool cask);

}

#endif // PROCESS_H
