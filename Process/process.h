#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

namespace qbrew
{

bool isBrewCaskInstalled();
std::pair<std::string, std::string> brewVersion();
std::vector<std::string> search(std::string search, bool isCask);
int install(std::string package, bool cask);
std::vector<std::string> listArgument(std::string argument);
std::vector<std::string> list(bool isCask);

}

#endif // PROCESS_H
