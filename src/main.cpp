#include "qbrewapplication.h"
#include <QApplication>
#include "db/db/dbmanager.h"
#include "db/db/qbrewdb.h"
#include "db/dto/packagedto.h"
#include "Process/process.h"
#include <QSqlDatabase>

#include "QDebug"
#include <QSettings>
#include <QTranslator>


using namespace qbrew;

int main(int argc, char * argv[])
{
    connection();
    //dropTable();

    QSqlDatabase db = QSqlDatabase::database();
    if (db.tables().isEmpty())
    {
        createTable();
        createDB(true); //db for brew cask
        createDB(false); //db for brew
    }

    removeAllInstalled();
    addListInstalled(list(true), true);
    addListInstalled(list(false), false);

    QBrewApplication app(argc, argv);

    QTranslator translator;
    qDebug() <<
             translator.load(":/Translations/qbrew_fr");
    qDebug() << app.installTranslator(&translator);

    //Valeur par défaut, à mettre parmis les fonctions
    //exécutées lors du premier lancement de l'application
    QSettings settings("Projet", "QBrew");
    settings.setValue("path", "/usr/local/HomeBrew");

    return app.exec();
    close();
}
