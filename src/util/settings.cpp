#include "settings.h"
#include <QSettings>

namespace qbrewutil
{

void initializeSettings()
{
    QSettings settings("Projet", "QBrew");
    if (!settings.contains("path"))
    {
        settings.setValue("path", "/usr/local/Homebrew");
    }
}

QString getBrewPath(bool cask)
{
    QSettings settings("Projet", "QBrew");
    QString path = settings.value("path").toString();
    QString homebrew = "/Library/Taps/homebrew/homebrew-core/Formula/";
    QString homebrewcask = "/Library/Taps/caskroom/homebrew-cask/Casks/";

    return cask ? path + homebrewcask : path + homebrew;
}

}
