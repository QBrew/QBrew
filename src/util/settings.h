#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

namespace qbrewutil
{

/*!
 * \brief Initialize settings
 */
void initializeSettings();

/*!
 * \brief Get the Homebrew path
 * \param cask True = get Homebrew Cask path, false = get Homebrew path
 * \return The asked for path
 */
QString getBrewPath(bool cask);

}

#endif // SETTINGS_H
