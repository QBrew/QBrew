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

QPair<QString, QString> brewVersion2();

void createDB(bool cask);

int install(std::string package, bool cask);
int install(QString package, bool cask);

std::vector<std::string> listArgument(std::string argument);
std::vector<std::string> list(bool isCask);

QMap<QString, QString> infoPackage(QString filename, bool cask);
void addToMap(QMap<QString, QString> & map, QStringList & infos, QString line);

void cleanup(bool cask);

}

#endif // PROCESS_H
