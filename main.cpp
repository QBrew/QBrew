#include "qbrewapplication.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char * argv[])
{

    qBrewApplication app(argc, argv);

    //Valeur par défaut, à mettre parmis les fonctions
    //exécutées lors du premier lancement de l'application
    QSettings settings("Projet","QBrew");
    settings.setValue("path","/usr/local/HomeBrew");
    //
    return app.exec();



    /*QApplication a(argc, argv);
    QBrew w;
    w.show();

    return a.exec();


    std::vector<std::string> test = qbrew::search("", false);

     for (std::string str : test)
     {
         std::cout << str << std::endl;
     }

     //std::cout << qbrew::install("vlc", true);

    return 0;*/
}
