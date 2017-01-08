#ifndef INFOBAR_H
#define INFOBAR_H

/*!
 * \file inforbar.h
 * \brief Info bar for the application
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "src/db/DTO/packagedto.h"

using namespace qbrewdb;

namespace qbrewview
{

/*!
 * \class infoBar
 * \brief The info bar of the application
 */
class infoBar : public QWidget
{
    Q_OBJECT
  public:

    /*!
     * \brief Constructor
     * \param parent Widget from which this infobar will depend
     */
    explicit infoBar(QWidget * parent = 0);

    /*!
     * \brief Update displayed information with given package information
     * \param package The package of which the information will be displayed
     */
    void updateInfo(PackageDTO package);

    /*!
     * \brief Creates all information labels
     */
    void initialize();

    /*!
     * \brief Clear all displayed information
     */
    void clear();

    /*!
     * \brief Create an hBox in which an information will be displayed
     * \param text The information that will be displayed
     * \return The created hbox
     */
    QHBoxLayout * hBoxCreator(QString text);

  signals:

  public slots:

  private:

    /*!
     * \brief Label for the name information
     */
    QLabel * name_;

    /*!
     * \brief Label for the file name information
     */
    QLabel * filename_;

    /*!
     * \brief Label for the version information
     */
    QLabel * version_;

    /*!
     * \brief Label for the url information
     */
    QLabel * url_;

    /*!
     * \brief Label for the homepage information
     */
    QLabel * homepage_;

    /*!
     * \brief Label for the description information
     */
    QLabel * desc_;
};

}

#endif // INFOBAR_H
