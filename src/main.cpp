#include "qbrewapplication.h"
#include <QApplication>
#include "DB/DB/dbmanager.h"
#include "DB/DB/qbrewdb.h"
#include "DB/DTO/formuladto.h"
#include "Process/process.h"
#include <QSqlDatabase>

#include "QDebug"
#include <QSettings>


using namespace qbrew;

int main(int argc, char * argv[])
{
    connection();
    //dropTable();

    QSqlDatabase db = QSqlDatabase::database();
    if (db.tables().isEmpty())
    {
        createTable();
        createDB(true);
    }

    updateInstalled(list());

    QBrewApplication app(argc, argv);

    //Valeur par défaut, à mettre parmis les fonctions
    //exécutées lors du premier lancement de l'application
    QSettings settings("Projet", "QBrew");
    settings.setValue("path", "/usr/local/HomeBrew");

    return app.exec();
    close();
}
