#ifndef PACKAGEDTO_H
#define PACKAGEDTO_H

#include <QString>
#include <QDebug>

namespace qbrew
{

class PackageDTO
{
  private :
    QString filename_;
    QString name_;
    QString version_;
    QString homepage_;
    QString url_;
    QString desc_;
    bool isInstalled_;
    bool isFavorite_;

  public:
    inline PackageDTO(QString filename, QString name, QString version,
                      QString homepage, QString url, QString desc,
                      bool isInstalled = false, bool isFavorite = false);
    inline PackageDTO() : PackageDTO("", "", "", "", "", "", false, false) {}
    inline const QString filename();
    inline const QString name();
    inline const QString version();
    inline const QString homepage();
    inline const QString url();
    inline const QString desc();
    inline bool isInstalled();
    inline bool isFavorite();
    inline void setIsInstalled(bool isInstalled);
    inline void setIsFavorite(bool isFavorite);

    QString toString();

};

PackageDTO::PackageDTO(QString filename, QString name, QString version,
                       QString homepage,
                       QString url, QString desc, bool isInstalled, bool isFavorite) :
    filename_ {filename}, name_{name}, version_{version}, homepage_{homepage}, url_{url},
    desc_{desc},
    isInstalled_{isInstalled}, isFavorite_{isFavorite}
{
}

const QString PackageDTO::filename()
{
    return filename_;
}

const QString PackageDTO::name()
{
    return name_;
}

const QString PackageDTO::version()
{
    return version_;
}

const QString PackageDTO::homepage()
{
    return homepage_;
}

const QString PackageDTO::url()
{
    return url_;
}

const QString PackageDTO::desc()
{
    return desc_;
}

bool PackageDTO::isInstalled()
{
    return isInstalled_;
}

bool PackageDTO::isFavorite()
{
    return isFavorite_;
}

void PackageDTO::setIsInstalled(bool isInstalled)
{
    isInstalled_ = isInstalled;
}

void PackageDTO::setIsFavorite(bool isFavorite)
{
    isFavorite_ = isFavorite;
}

}

#endif // PACKAGEDTO_H
