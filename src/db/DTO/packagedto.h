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
    bool isCask_;
    bool isInstalled_;
    bool isFavorite_;

  public:
    inline PackageDTO(QString filename, QString name, QString version,
                      QString homepage, QString url, QString desc,
                      bool isCask, bool isInstalled, bool isFavorite);
    inline PackageDTO() : PackageDTO("", "", "", "", "", "",false, false, false) {}

    inline QString filename() const;
    inline QString name() const;
    inline QString version() const;
    inline QString homepage() const;
    inline QString url() const;
    inline QString desc() const;
    inline bool isCask();
    inline bool isInstalled();
    inline bool isFavorite();
    inline void setIsInstalled(bool isInstalled);
    inline void setIsFavorite(bool isFavorite);

    QString toString();

};

PackageDTO::PackageDTO(QString filename, QString name, QString version,
                       QString homepage, QString url, QString desc,
                       bool isCask, bool isInstalled, bool isFavorite) :
    filename_ {filename}, name_{name}, version_{version}, homepage_{homepage}, url_{url},
    desc_{desc}, isCask_{isCask}, isInstalled_{isInstalled}, isFavorite_{isFavorite}
{
}

QString PackageDTO::filename() const
{
    return filename_;
}

QString PackageDTO::name() const
{
    return name_;
}

QString PackageDTO::version() const
{
    return version_;
}

QString PackageDTO::homepage() const
{
    return homepage_;
}

QString PackageDTO::url() const
{
    return url_;
}

QString PackageDTO::desc() const
{
    return desc_;
}

bool PackageDTO::isCask()
{
    return isCask_;
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
