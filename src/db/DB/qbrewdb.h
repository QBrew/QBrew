#ifndef QBREWDB_H
#define QBREWDB_H

/*!
 * \file qbrewdb.h
 * \brief Database for homebrew and homebrew cask packages
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QList>
#include "../dto/packagedto.h"

namespace qbrew
{
QList<PackageDTO> getFavourites();

/*!
 * \brief Getter for list with installed packages only
 * \return List with installed packages only
 */
QList<PackageDTO> getInstalled();

/*!
 * \brief Getter for list with packages matching given string
 * \param searchValue string to match to packages name
 * \return List with packages matching given string
 */
QList<PackageDTO> getSearch(QString searchValue);

/*!
 * \brief Get single package with matching filename
 * \param filename the name of the file of the package
 * \param isCask wether that package is a homebrew cask package or not
 * \return
 */
PackageDTO selectPackage(QString filename, bool isCask);

/*!
 * \brief Insert given package into the database
 * \param package the package to insert
 * \return true if insertion was succesful, false otherwise
 */
bool addPackage(PackageDTO package);

/*!
 * \brief set package matching filename to favourite in the database
 * \param filename the name of the file of the package
 * \param isCask wether the package is a homebrew cask package or not
 */
void addFavourite(QString filename, bool isCask);

/*!
 * \brief update package in database with given package information
 * \param package the updated package information
 */
void updateFavourite(PackageDTO package);

/*!
 * \brief delete package from its filename in the database
 * \param filename name of the file of the package to delete
 * \param isCask wether the package is  homebrew cask package or not
 */
void deletePackage(QString filename, bool isCask);

/*!
 * \brief Set list of packages to installed in the database
 * \param filenames list of filenames of all the packages to update
 * \param isCask wether those packages are homebrew cask packages or not
 */
void addListInstalled(QStringList filenames, bool isCask);

/*!
 * \brief set given package to installed in the database
 * \param package the package to update
 */
void addInstalled(PackageDTO package);

/*!
 * \brief set package matching filename to installed in the database
 * \param filename the name of the file of the package
 * \param isCask wether the package is a homebrew cask package or not
 */
void addInstalled(QString filename, bool isCask);

/*!
 * \brief Set given package to uninstalled in the database
 * \param package the package to update
 */
void removeInstalled(PackageDTO package);

/*!
 * \brief set package matching filename to uninstalled in the database
 * \param filename name of the file of the package
 * \param isCask wether the package is a homebrew cask package or not
 */
void removeInstalled(QString filename, bool isCask);

/*!
 * \brief Set all installed packages in the database to uninstalled
 */
void removeAllInstalled();

/*!
 * \brief Set all favourite packages in the database to unfavourite
 */
void removeAllFavourites();
}

#endif // QBREWDB_H
