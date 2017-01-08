#ifndef PREFERENCES_H
#define PREFERENCES_H

/*!
 * \file preferences.h
 * \brief The preferences window
 * \author Cédric Gilon, Arnaud De Bruecker, Quentin Ravau
 */

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <iostream>
#include <QFile>
#include <QLineEdit>
#include <QSettings>

namespace qbrewview
{

/*!
 * \class Preferences
 * \brief The preferences window
 */
class Preferences : public QDialog
{
    Q_OBJECT
  public:

    /*!
     * \brief Constructor
     * \param Parent The widget from which this preferences window will depend
     */
    Preferences(QWidget * Parent);

    /*!
     * \brief Set line edit in window with value from QSettings
     */
    void setTextZone();

    /*!
     * \brief Set all buttons of the window and connect them to their function
     */
    void setButtons();

  signals:

  public slots:

    /*!
     * \brief Save the new line edit to QSettings
     */
    void save();

    /*!
     * \brief Open fileDialog window to set a new path in line edit
     */
    void getDirectory();

  private :

    /*!
     * \brief The main layout of the window
     */
    QVBoxLayout * vbox_;

    /*!
     * \brief The line edit to display and modify Homebrew path
     */
    QLineEdit * path_;

    /*!
     * \brief The button to close the window
     */
    QPushButton * closeButton_;

    /*!
     * \brief The button to save the new path then close the window
     */
    QPushButton * saveButton_;

    /*!
     * \brief The button to open the file dialog window
     */
    QPushButton * pathButton_;
};
}
#endif // PREFERENCES_H
