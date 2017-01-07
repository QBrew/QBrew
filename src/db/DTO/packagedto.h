#ifndef PACKAGEDTO_H
#define PACKAGEDTO_H

/*!
 * \file packagedto.h
 * \brief database access for packages
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QString>
#include <QDebug>

namespace qbrew
{

/*!
 * \class PackageDTO
 * \brief database access for packages
 */
class PackageDTO
{
  private :

    /*!
     * \brief the name of the file of the package
     */
    QString filename_;

    /*!
     * \brief The name of the package
     */
    QString name_;

    /*!
     * \brief The version of the package
     */
    QString version_;

    /*!
     * \brief the homepage for the package maker
     */
    QString homepage_;

    /*!
     * \brief The url for more information about the package
     */
    QString url_;

    /*!
     * \brief The description of the package
     */
    QString desc_;

    /*!
     * \brief Indicates wether package is a cask package or not
     */
    bool isCask_;

    /*!
     * \brief Indicates wether package is installed or not
     */
    bool isInstalled_;

    /*!
     * \brief Indicates wether package is favourite or not
     */
    bool isFavourite_;

  public:

    /*!
     * \brief Constructor
     * \param filename name of the file of the package
     * \param name name of the package
     * \param version version of the package
     * \param homepage homepage of the package maker
     * \param url url for more information about the package
     * \param desc description of the package
     * \param isCask wether package is a cask package or not
     * \param isInstalled wether package is installed or not
     * \param isFavourite wether package is favourite or not
     */
    inline PackageDTO(QString filename, QString name, QString version,
                      QString homepage, QString url, QString desc,
                      bool isCask, bool isInstalled, bool isFavourite);

    /*!
     * \brief Default constructor
     */
    inline PackageDTO() : PackageDTO("", "", "", "", "", "",false, false, false) {}

    /*!
     * \brief Getter for filename information
     * \return filename_
     */
    inline QString filename() const;

    /*!
     * \brief Getter for name information
     * \return name_
     */
    inline QString name() const;

    /*!
     * \brief Getter for version information
     * \return version_
     */
    inline QString version() const;

    /*!
     * \brief Getter for homepage information
     * \return homepage_
     */
    inline QString homepage() const;

    /*!
     * \brief Getter for url information
     * \return url_
     */
    inline QString url() const;

    /*!
     * \brief Getter for description information
     * \return desc_
     */
    inline QString desc() const;

    /*!
     * \brief Getter for isCask information
     * \return isCask_
     */
    inline bool isCask();

    /*!
     * \brief Getter for isInstalled information
     * \return isInstalled_
     */
    inline bool isInstalled();

    /*!
     * \brief Getter for isFavourite information
     * \return isFavourite_
     */
    inline bool isFavourite();

    /*!
     * \brief Setter for isInstalled information
     * \param isInstalled The new value
     */
    inline void setIsInstalled(bool isInstalled);

    /*!
     * \brief Setter for isFavourite information
     * \param isFavourite The new value
     */
    inline void setIsFavourite(bool isFavourite);

    /*!
     * \brief Caster to string
     * \return string with all information
     */
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
