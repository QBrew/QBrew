#ifndef FAVORITEDTO_H
#define FAVORITEDTO_H

#include <QString>

namespace qbrew
{

class FavoriteDTO
{

  private:
    const QString name_;

  public:
    inline FavoriteDTO(QString name);
    inline QString name();
};

FavoriteDTO::FavoriteDTO(QString name) : name_{name}
{
}

QString FavoriteDTO::name()
{
    return name_;
}

}

#endif // FAVORITEDTO_H
