#ifndef PROCESS_H
#define PROCESS_H

/*!
 * \file process.h
 * \brief The homebrew processes
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <string>
#include <vector>
#include <QMap>
#include <QFileInfoList>
#include "../db/db/qbrewdb.h"

namespace qbrew
{

/*!
 * \brief Checks if homebrew cask is installed on machine
 * \return true if homebrew cask is installed, false otherwise
 */
bool isBrewCaskInstalled();

/*!
 * \brief Get the homebrew path
 * \param cask true = get homebrew cask path, false = get homebrew path
 * \return the asked for path
 */
QString getBrewPath(bool cask);

/*!
 * \brief Get version of homebrew and homebrew cask
 * \return QPair with homebrew version and homebrew cask version
 */
QPair<QString, QString> brewVersion();

/*!
 * \brief create database with all packages
 * \param cask true = homebrew cask packages, false = homebrew packages
 */
void createDB(bool cask);

/*!
 * \brief Install desired package
 * \param package The package to install
 * \return 0 if succesful, -1 if error
 */
int install(PackageDTO package);

/*!
 * \brief uninstall desired package
 * \param package The package to uninstall
 * \return 0 if succesful, -1 if error
 */
int uninstall(PackageDTO package);

/*!
 * \brief execute the brew update command
 */
void updateHomebrew();

/*!
 * \brief Get list of all packages
 * \param isCask true = homebrew cask packages, false = homebrew packages
 * \return list of string of packages
 */
QStringList list(bool isCask);

/*!
 * \brief Get list of packages matching argument
 * \param argument The searched for package
 * \return QStringList of packages matching argument
 */
QStringList listArgument(QString argument);

/*!
 * \brief Get all informations from package in given homebrew file
 * \param filename The desired homebrew file
 * \param cask true = homebrew cask file, false = homebrew file
 * \return Map of information concerning package
 */
QMap<QString, QString> infoPackage(QString filename, bool cask);

/*!
 * \brief addToMap
 * \param map
 * \param infos
 * \param line
 */
void addToMap(QMap<QString, QString> & map, QStringList & infos, QString line);

/*!
 * \brief Execute the brew cleanup or brew cask cleanuo command
 * \param cask true = brew cask cleanup, false = brew cleanup
 */
void cleanup(bool cask);

}

#endif // PROCESS_H
