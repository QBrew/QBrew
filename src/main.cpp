#include "qbrewapplication.h"
#include "db/db/dbmanager.h"
#include "util/settings.h"

#include <QSqlDatabase>
#include <QSettings>

/*!
  * \mainpage QBrew
  * HE2B-ESI\n
  * C++ Project\n
  * 2016-2017\n
  * Arnaud DE BRUECKER (40894)\n
  * Cédric GILON (41674)\n
  * Quentin RAVAU (42586)
  */

int main(int argc, char * argv[])
{
    qbrewdb::initializeDB();
    qbrewutil::initializeSettings();

    qbrewview::QBrewApplication app(argc, argv);
    return app.exec();
    close();
}
