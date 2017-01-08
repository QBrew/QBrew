#ifndef ABOUT_H
#define ABOUT_H

/*!
 * \file about.h
 * \brief The about window
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

/*!
 * \class About
 * \brief The about window popup
 */
class About : public QDialog
{
  public:

    /*!
     * \brief Constructor
     * \param parent The widget from which this about window will depend
     */
    About(QWidget * parent);

    /*!
     * \brief Set the text displayed in the window
     */
    void setText();

    /*!
     * \brief Set a close button at the bottom of the window
     */
    void setButton();

  signals:

  public slots:

  private:

    /*!
     * \brief The main layout of the window
     */
    QVBoxLayout * vbox_;

    /*!
     * \brief The text displayed in the window
     */
    QLabel * text_;

    /*!
     * \brief The close button for the window
     */
    QPushButton * closeButton_;
};

#endif // ABOUT_H
