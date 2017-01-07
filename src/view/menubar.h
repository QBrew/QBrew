#ifndef MENUBAR_H
#define MENUBAR_H

/*!
 * \file menubar.h
 * \brief Menu bar for the application
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QMenuBar>
#include "../view/packagelist.h"
#include "../menu/about.h"
#include "../menu/preferences.h"

/*!
 * \class MenuBar
 * \brief Menu bar for the application
 */
class MenuBar : public QMenuBar
{
  public:

    /*!
     * \brief Constructor
     * \param parent widget from which this menubar will depend
     * \param list list of packages that the menubar will modify
     */
    MenuBar(QWidget * parent, qbrew::PackageList * list);

    /*!
     * \brief Set all actions in matching menu
     */
    void setActions();

    /*!
     * \brief Connect all actions to their function
     */
    void setConnections();

    /*!
     * \brief Ask for an about window to be created
     */
    void aboutPopup();

    /*!
     * \brief Ask for a preference window to be created
     */
    void preferencesPopup();

    /*!
     * \brief Ask for an import window to be created
     */
    void importPopup();

    /*!
     * \brief Ask for an export window to be created
     */
    void exportPopup();

  signals:

  public slots:

  private:
    /*!
     * \brief The main menu from the menubar
     */
    QMenu * menu_;

    /*!
     * \brief The favourites menu from the menubar
     */
    QMenu * favourites_;

    /*!
     * \brief Action that will trigger the about popup
     */
    QAction * aboutAction_;

    /*!
     * \brief Action that will trigger the preferences popup
     */
    QAction * preferencesAction_;

    /*!
     * \brief Action that will trigger the import popup
     */
    QAction * importFavourites_;

    /*!
     * \brief Action that will trigger the export popup
     */
    QAction * exportFavourites_;

    /*!
     * \brief The list of packages the menubar actions will update
     */
    qbrew::PackageList * list_;
};

#endif // MENUBAR_H
