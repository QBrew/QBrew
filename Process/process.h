#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

namespace qbrew
{

bool isBrewCaskInstalled();
std::pair<std::string, std::string> brewVersion();
std::vector<std::string> search(std::string search, bool cask);
int install(std::string package, bool cask);

}

#endif // PROCESS_H
