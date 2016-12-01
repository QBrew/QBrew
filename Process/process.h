#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <QMap>
#include <QFileInfoList>

namespace qbrew
{

bool isBrewCaskInstalled();

std::pair<std::string, std::string> brewVersion();
QPair<QString, QString> brewVersion2();

std::vector<std::string> search(std::string search, bool isCask);
QFileInfoList search2(QString searchValue, bool isCask = true);

int install(std::string package, bool cask);
std::vector<std::string> listArgument(std::string argument);
std::vector<std::string> list(bool isCask);
QMap<std::string, std::string> infoPackage(std::string package,
        bool isCask);

}

#endif // PROCESS_H
