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
    bool isFavourite_;

  public:
    inline PackageDTO(QString filename, QString name, QString version,
                      QString homepage, QString url, QString desc,
                      bool isCask, bool isInstalled, bool isFavourite);
    inline PackageDTO() : PackageDTO("", "", "", "", "", "",false, false, false) {}

    inline QString filename() const;
    inline QString name() const;
    inline QString version() const;
    inline QString homepage() const;
    inline QString url() const;
    inline QString desc() const;
    inline bool isCask() const;
    inline bool isInstalled() const;
    inline bool isFavourite() const;
    inline void setIsInstalled(bool isInstalled);
    inline void setIsFavourite(bool isFavourite);

    QString toString();

};

PackageDTO::PackageDTO(QString filename, QString name, QString version,
                       QString homepage, QString url, QString desc,
                       bool isCask, bool isInstalled, bool isFavourite) :
    filename_ {filename}, name_{name}, version_{version}, homepage_{homepage}, url_{url},
    desc_{desc}, isCask_{isCask}, isInstalled_{isInstalled}, isFavourite_{isFavourite}
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

bool PackageDTO::isCask() const
{
    return isCask_;
}

bool PackageDTO::isInstalled() const
{
    return isInstalled_;
}

bool PackageDTO::isFavourite() const
{
    return isFavourite_;
}

void PackageDTO::setIsInstalled(bool isInstalled)
{
    isInstalled_ = isInstalled;
}

void PackageDTO::setIsFavourite(bool isFavourite)
{
    isFavourite_ = isFavourite;
}

}

#endif // PACKAGEDTO_H
