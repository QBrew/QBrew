/*!
 * \file process.h
 * \brief The Homebrew processes
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <QMap>
#include <QString>
#include <QFileInfoList>
#include "../db/db/dbactions.h"

using namespace qbrewdb;

namespace qbrewprocess
{

void initializeSettings();

/*!
 * \brief Checks if Homebrew cask is installed on machine
 * \return True if Homebrew cask is installed, false otherwise
 */
bool isBrewCaskInstalled();

/*!
 * \brief Get the Homebrew path
 * \param cask True = get Homebrew Cask path, false = get Homebrew path
 * \return The asked for path
 */
QString getBrewPath(bool cask);

/*!
 * \brief Get version of Homebrew and Homebrew cask
 * \return QPair with Homebrew version and Homebrew Cask version
 */
QPair<QString, QString> brewVersion();

/*!
 * \brief Create database with all packages
 * \param cask True = Homebrew Cask packages, false = Homebrew packages
 */
void createDB(bool cask);

/*!
 * \brief Install desired package
 * \param package The package to install
 * \return 0 if succesful, -1 if error
 */
int install(PackageDTO package);

/*!
 * \brief Uninstall desired package
 * \param package The package to uninstall
 * \return 0 if succesful, -1 if error
 */
int uninstall(PackageDTO package);

/*!
 * \brief Execute the brew update command
 */
void updateHomebrew();

/*!
 * \brief Get list of all packages
 * \param isCask True = Homebrew Cask packages, false = Homebrew packages
 * \return List of string of packages
 */
QStringList list(bool isCask);

/*!
 * \brief Get list of packages matching argument
 * \param argument The searched for package
 * \return QStringList of packages matching argument
 */
QStringList listArgument(QString argument);

/*!
 * \brief Get all informations from package in given Homebrew file
 * \param filename The desired Homebrew file
 * \param cask true = Homebrew Cask file, false = Homebrew file
 * \return Map of information concerning package
 */
QMap<QString, QString> infoPackage(QString filename, bool cask);

/*!
 * \brief Add the info to the map if exist
 * \param map The map
 * \param infos The remaining infos to find
 * \param line The line
 */
void addToMap(QMap<QString, QString> & map, QStringList & infos, QString line);

/*!
 * \brief Execute the brew cleanup or brew cask cleanuo command
 * \param cask True = brew cask cleanup, false = brew cleanup
 */
void cleanup(bool cask);

}

#endif // PROCESS_H
