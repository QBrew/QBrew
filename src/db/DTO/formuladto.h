#ifndef FORMULADTO_H
#define FORMULADTO_H

#include <QString>
#include <QDebug>

namespace qbrew
{

class FormulaDTO
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
    inline FormulaDTO(QString filename, QString name, QString version,
                      QString homepage, QString url, QString desc,
                      bool isInstalled = false, bool isFavorite = false);
    inline FormulaDTO() : FormulaDTO("", "", "", "", "", "", false, false) {}
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

FormulaDTO::FormulaDTO(QString filename, QString name, QString version, QString homepage,
                       QString url, QString desc, bool isInstalled, bool isFavorite) :
    filename_ {filename}, name_{name}, version_{version}, homepage_{homepage}, url_{url}, desc_{desc},
    isInstalled_{isInstalled}, isFavorite_{isFavorite}
{
}

const QString FormulaDTO::filename()
{
    return filename_;
}

const QString FormulaDTO::name()
{
    return name_;
}

const QString FormulaDTO::version()
{
    return version_;
}

const QString FormulaDTO::homepage()
{
    return homepage_;
}

const QString FormulaDTO::url()
{
    return url_;
}

const QString FormulaDTO::desc()
{
    return desc_;
}

bool FormulaDTO::isInstalled()
{
    return isInstalled_;
}

bool FormulaDTO::isFavorite()
{
    return isFavorite_;
}

void FormulaDTO::setIsInstalled(bool isInstalled)
{
    isInstalled_ = isInstalled;
}

void FormulaDTO::setIsFavorite(bool isFavorite)
{
    isFavorite_ = isFavorite;
}

}

#endif // FORMULADTO_H
