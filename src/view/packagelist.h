#ifndef PACKAGELIST_H
#define PACKAGELIST_H

/*!
 * \file packagelist.h
 * \brief List of all the packages of homebrew
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QTableWidget>
#include <QCheckBox>
#include <QList>
#include <QIcon>
#include <src/db/DTO/packagedto.h>

namespace qbrew
{

/*!
 * \class PackageList
 * \brief List of all the packages of homebrew
 */
class PackageList : public QTableWidget
{
    Q_OBJECT

    /*!
     * \brief Status string indicating wether displayed list is set on favourite, installed or search
     */
    QString status_;

    /*!
     * \brief List of homebrew packages to display
     */
    QList<PackageDTO> packages_;

    /*!
     * \brief List of all checkboxes matching their package
     */
    QList<QCheckBox *> checkBoxes_;

    /*!
     * \brief The favourite icon
     */
    QIcon favouriteIcon_;

    /*!
     * \brief The not favourite icon
     */
    QIcon noFavouriteIcon_;

    /*!
     * \brief List of all the icons used for installed and favourite status
     */
    QList<QIcon> statusIcons_;
    int row_;


  public:
    /*!
     * \brief Constructor
     * \param parent widget from which this list will depend
     */
    explicit PackageList(QWidget * parent = 0);

    /*!
     * \brief Set list of packages to favourite only
     */
    void setFavourite();

    /*!
     * \brief Set list of packages to installed only
     */
    void setInstalled();

    /*!
     * \brief Set the icons used for installed and favourite status
     */
    void setIcons();

    /*!
     * \brief Getter for selected package at private attribute row_
     * \return selected PackageDTO
     */
    PackageDTO selected();

    /*!
     * \brief Getter for selected package at specified position
     * \param row specified position for desired package
     * \return Seleected PackageDTO
     */
    PackageDTO getPackage(int row);

    /*!
     * \brief Set list to packages matching searched string
     * \param searchValue The searched string in the packages
     */
    void setSearch(QString searchValue);

    /*!
     * \brief update the viewed list
     */
    void update();

    /*!
     * \brief Select or unselect all packages
     * \param isAll true = select all, false = unselect all
     */
    void setSelectPackage(bool isAll);

    /*!
     * \brief Getter for list of selected packages
     * \return QList of all selected packages
     */
    QList<PackageDTO> listSelected();

    /*!
     * \brief Click action on a package
     * \param row row of package in list of packages
     * \param column column of package in list of packages
     */
    void tableItemClicked(int row, int column);

    /*!
     * \brief Double click action on a package
     * \param row row of package in list of packages
     * \param column column of package in list of packages
     */
    void tableItemDoubleClicked(int row, int column);

    /*!
     * \brief Getter for status_ QString
     * \return status_
     */
    QString getStatus() const;

  private:

    /*!
     * \brief Match displayed list to packages_ list
     */
    void setList();

    /*!
     * \brief Align given checkbox to specific location in returned widget
     * \param cb The checkbox to align
     * \return The widget with the aligned checkbox in it
     */
    QWidget * alignCheckBox(QCheckBox * cb);
  signals:

    /*!
     * \brief Signal to inform that the clicked on item has changed
     */
    void clickedItemChange();

  public slots:

};

}

#endif // PACKAGELIST_H
