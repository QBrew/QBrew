#ifndef TOOLBAR_H
#define TOOLBAR_H

/*!
 * \file toolbar.h
 * \brief Toolbar of the main window
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QAction>
#include <QToolBar>
#include <QLineEdit>

namespace qbrewview
{

/*!
 * \class ToolBar
 * \brief Toolbar of the main window
 */
class ToolBar : public QToolBar
{
    Q_OBJECT

    /*!
     * \brief The update action
     */
    QAction * updateAction_;

    /*!
     * \brief The install action
     */
    QAction * installAction_;

    /*!
     * \brief The uninstall action
     */
    QAction * uninstallAction_;

    /*!
     * \brief The favourite action
     */
    QAction * favouriteAction_;

    /*!
     * \brief The remove favourite action
     */
    QAction * removeFavouriteAction_;

    /*!
     * \brief The select all action
     */
    QAction * selectAll_;

    /*!
     * \brief The select Nonne action
     */
    QAction * selectNone_;

    /*!
     * \brief The line edit used for searching packages
     */
    QLineEdit * searchField_;

    /*!
     * \brief Set all actions in the tool bar
     */
    void setActions();

    /*!
     * \brief Connect all actions to their signal
     */
    void setConnections();

    /*!
     * \brief Set status tips for all actions
     */
    void setStatusTips();

    /*!
     * \brief Set tool tips for all actions
     */
    void setToolTips();

    /*!
     * \brief setSearchField
     */
    void setSearchField();

  public:
    /*!
     * \brief Constructor
     * \param parent Widget from which this toolbar will depend
     */
    explicit ToolBar(QWidget * parent = 0);

    /*!
     * \brief Getter for searchfield_
     * \return searchfield_
     */
    QLineEdit * searchField() const;

  signals:
    /*!
     * \brief Signal for update action clicked
     */
    void updateClicked();

    /*!
     * \brief Signal for install action clicked
     */
    void installClicked();

    /*!
     * \brief Signal for uninstall action clicked
     */
    void uninstallClicked();

    /*!
     * \brief Signal for add favourite action clicked
     */
    void addFavouriteClicked();

    /*!
     * \brief Signal for remove favourite action clicked
     */
    void removeFavouriteClicked();

    /*!
     * \brief Signal for select all action clicked
     */
    void selectAllClicked();

    /*!
     * \brief Signal for select none action clicked
     */
    void selectNoneClicked();

    /*!
     * \brief Signal for search action clicked
     */
    void searchPressed();
};

}

#endif // TOOLBAR_H
