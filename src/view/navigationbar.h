#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

/*!
 * \file navigationbar.h
 * \brief Navigation bar for the application
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QWidget>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>

namespace qbrewview
{

/*!
 * \class NavigationBar
 * \brief Navigation bar for the application
 */
class NavigationBar : public QWidget
{
    Q_OBJECT

    /*!
     * \brief Setter for all buttons in the navigation bar
     */
    void setButtons();

  public:
    /*!
     * \brief Constructor
     * \param parent Widget from which this navigation bar will depend
     */
    explicit NavigationBar(QWidget * parent = 0);

    /*!
     * \brief Getter for installed_ QPushButton
     * \return installed_
     */
    inline QPushButton * installed();

    /*!
     * \brief Getter for favourite_ QPushButton
     * \return favourite_
     */
    inline QPushButton * favourite();

    /*!
     * \brief Getter for group_ QButtonGroup
     * \return group_
     */
    inline QButtonGroup * group();

  signals:

  public slots:

  private:

    /*!
     * \brief The QButtonGroup in which all QPushButtons will be placed
     */
    QButtonGroup * group_;

    /*!
     * \brief The installed QPushButton
     */
    QPushButton * installed_;

    /*!
     * \brief The favourite QPushButton
     */
    QPushButton * favourite_;

    /*!
     * \brief The QVBoxLayout in which all buttons will be placed
     */
    QVBoxLayout * vBox_;

    /*!
     * \brief Creates a QPushButton with desired style
     * \param name Name given to the button
     * \return The created QPushButton
     */
    QPushButton * getPushButton(const QString & name);
};


QPushButton * NavigationBar::installed()
{
    return installed_;
}

QPushButton * NavigationBar::favourite()
{
    return favourite_;
}

QButtonGroup * NavigationBar::group()
{
    return group_;
}

}

#endif // NAVIGATIONBAR_H
