#ifndef QBREWDB_H
#define QBREWDB_H

/*!
 * \file qbrewdb.h
 * \brief Database for Homebrew and Homebrew Cask packages
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QList>
#include "../dto/packagedto.h"

namespace qbrewdb
{

/*!
 * \brief Getter for list with favourite packages only
 * \return List with favourite packages only
 */
QList<PackageDTO> getFavourites();

/*!
 * \brief Getter for list with installed packages only
 * \return List with installed packages only
 */
QList<PackageDTO> getInstalled();

/*!
 * \brief Getter for list with packages matching given string
 * \param searchValue String to match to packages name
 * \return List with Packages matching given string
 */
QList<PackageDTO> getSearch(QString searchValue);

/*!
 * \brief Get single package with matching filename
 * \param filename The name of the file of the package
 * \param isCask Wether that package is a Homebrew Cask package or not
 * \return Selected package
 */
PackageDTO selectPackage(QString filename, bool isCask);

/*!
 * \brief Insert given package into the database
 * \param package The package to insert
 * \return True if insertion was succesful, false otherwise
 */
bool addPackage(PackageDTO package);

/*!
 * \brief Set package matching filename to favourite in the database
 * \param filename The name of the file of the package
 * \param isCask Wether the package is a Homebrew Cask package or not
 */
void addFavourite(QString filename, bool isCask);

/*!
 * \brief update Package in database with given package information
 * \param package The updated package information
 */
void updateFavourite(PackageDTO package);

/*!
 * \brief Delete package from its filename in the database
 * \param filename Name of the file of the package to delete
 * \param isCask Wether the package is  Homebrew Cask package or not
 */
void deletePackage(QString filename, bool isCask);

/*!
 * \brief Set list of packages to installed in the database
 * \param filenames List of filenames of all the packages to update
 * \param isCask Wether those packages are Homebrew Cask packages or not
 */
void addListInstalled(QStringList filenames, bool isCask);

/*!
 * \brief Set given package to installed in the database
 * \param Package the package to update
 */
void addInstalled(PackageDTO package);

/*!
 * \brief Set package matching filename to installed in the database
 * \param filename The name of the file of the package
 * \param isCask Wether the package is a Homebrew Cask package or not
 */
void addInstalled(QString filename, bool isCask);

/*!
 * \brief Set given package to uninstalled in the database
 * \param package the package to update
 */
void removeInstalled(PackageDTO package);

/*!
 * \brief Set package matching filename to uninstalled in the database
 * \param filename Name of the file of the package
 * \param isCask Wether the package is a Homebrew Cask package or not
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
