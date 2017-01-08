/*!
 * \file dbmanager.h
 * \brief Basic SQL scripts of the database
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#ifndef DBMANAGER_H
#define DBMANAGER_H

namespace qbrewdb
{

void initializeDB();
/*!
 * \brief Create a connection to the database
 * \return true if connection succeeded, false otherwise
 */
bool connection();

/*!
 * \brief Close the database if it is open
 */
void close();

/*!
 * \brief Create PACKAGES table with set conditions
 */
void createTable();

/*!
 * \brief Drop PACKAGES table
 */
void dropTable();

}

#endif // DBMANAGER_H
