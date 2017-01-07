#ifndef DBMANAGER_H
#define DBMANAGER_H

/*!
 * \file dbmanager.h
 * \brief Basic sql scripts of the database
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

namespace qbrew
{

/*!
 * \brief inicates wether connection is succesful or not
 * \return true if connection succeeded, false otherwise
 */
bool connection();

/*!
 * \brief close the database if it is open
 */
void close();

/*!
 * \brief create sql table with set conditions
 */
void createTable();

/*!
 * \brief drop sql table
 */
void dropTable();

}

#endif // DBMANAGER_H
