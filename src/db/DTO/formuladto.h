#ifndef FORMULADTO_H
#define FORMULADTO_H

#include <QString>
#include <QDebug>

namespace qbrew
{

class FormulaDTO
{
  private :
    QString name_;
    QString version_;
    QString homepage_;
    QString url_;
    QString desc_;
    bool isInstalled_;
    bool isFavorite_;

  public:
    inline FormulaDTO(QString name, QString version, QString homepage,
                      QString url, QString desc,
                      bool isInstalled = false, bool isFavorite = false);
    inline FormulaDTO() : FormulaDTO("", "", "", "", "", false, false) {}
    inline const QString name();
    inline const QString version();
    inline const QString homepage();
    inline const QString url();
    inline const QString desc();
    inline bool isInstalled();
    inline bool isFavorite();

    QString toString();

};

FormulaDTO::FormulaDTO(QString name, QString version, QString homepage,
                       QString url, QString desc, bool isInstalled, bool isFavorite) :
    name_{name}, version_{version}, homepage_{homepage}, url_{url}, desc_{desc},
    isInstalled_{isInstalled}, isFavorite_{isFavorite}
{
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

}

#endif // FORMULADTO_H
