#include "qbrewapplication.h"
#include <QApplication>
#include "DB/DB/dbmanager.h"
#include "DB/DB/qbrewdb.h"
#include "DB/DTO/formuladto.h"
#include "Process/process.h"
#include <QSqlDatabase>

#include "QDebug"

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

    qBrewApplication app(argc, argv);

    //Valeur par défaut, à mettre parmis les fonctions
    //exécutées lors du premier lancement de l'application
    QSettings settings("Projet","QBrew");
    settings.setValue("path","/usr/local/HomeBrew");
    //
    return app.exec();
    close();
    /*
    connection();
    //dropTable();
    //createTable();
    FormulaDTO formula("un 4e package", "12.23", "www.monurl.com",
                       "www.monurl.dl.com", "Bonjour!", true, false);
    if (addFormula(formula))
    {
        //qDebug() << "Formula added";
    }
    //deleteFormula("un 3e package");
    for (auto f : getAll())
    {
        qDebug().noquote() << f.toString();
        qDebug() << "";
    }
    return 0;
    */
}
