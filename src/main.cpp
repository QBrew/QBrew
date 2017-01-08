#include "qbrewapplication.h"
#include <QApplication>
#include "db/db/dbmanager.h"
#include "db/db/dbactions.h"
#include "db/dto/packagedto.h"
#include "Process/process.h"
#include <QSqlDatabase>
#include "QDebug"
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

using namespace qbrewview;

int main(int argc, char * argv[])
{
    qbrewdb::initialize();
    QBrewApplication app(argc, argv);

    //Valeur par défaut, à mettre parmis les fonctions
    //exécutées lors du premier lancement de l'application
    QSettings settings("Projet", "QBrew");
    settings.setValue("path", "/usr/local/HomeBrew");

    return app.exec();
    close();
}
