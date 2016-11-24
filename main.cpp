#include "qbrewapplication.h"
#include <QApplication>

int main(int argc, char * argv[])
{

    qBrewApplication app(argc, argv);
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
