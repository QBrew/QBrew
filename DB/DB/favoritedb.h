#ifndef FAVORITEDB_H
#define FAVORITEDB_H

#include "DB/DTO/favoritedto.h"
#include <QList>

namespace qbrew
{

void createTableFavorite();

QList<QString> getAllFavorite();
bool addToFavorite(QString fav);
bool removeFromFavorite(QString fav);

}

#endif // FAVORITEDB_H
