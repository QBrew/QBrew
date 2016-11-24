#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <map>

namespace qbrew
{

bool isBrewCaskInstalled();
std::pair<std::string, std::string> brewVersion();
std::vector<std::string> search(std::string search, bool isCask);
int install(std::string package, bool cask);
std::vector<std::string> listArgument(std::string argument);
std::vector<std::string> list(bool isCask);
std::map<std::string, std::string> infoPackage(std::string package,
        bool isCask);

}

#endif // PROCESS_H
