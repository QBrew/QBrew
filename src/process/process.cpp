#include "process.h"
#include <sstream>
#include <iostream>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include "../db/dto/packagedto.h"
#include "../db/db/dbactions.h"

#include <QDebug>

namespace qbrewprocess
{

QString getBrewPath(bool cask)
{
    //TODO check if path is no default

    return cask ?
           "/usr/local/Homebrew/Library/Taps/caskroom/homebrew-cask/Casks/" :
           "/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/";
}

bool isBrewCaskInstalled()
{
    QProcess process;
    QString str = "/usr/local/bin/brew --version ";
    process.start(str);
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();

    return !stdout.isEmpty();
}

QPair<QString, QString> brewVersion()
{
    QProcess process;
    process.start("/usr/local/bin/brew --version ");
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();
    QString brew = stdout.split("\n").at(0).split(" ").at(1);

    process.start("/usr/local/bin/brew cask --version ");
    process.waitForFinished(-1); // will wait forever until finished
    stdout = process.readAllStandardOutput();
    QString brewCask = stdout.split("\n").at(0).split(" ").at(1);

    return QPair<QString, QString> (brew, brewCask);
}

int install(PackageDTO package)
{
    QString command = "/usr/local/bin/brew ";
    command.append(package.isCask() ? "cask install " : "install ");
    command.append(package.filename());

    QProcess process;
    process.start(command);
    process.waitForFinished(-1); // will wait forever until finished

    if (process.exitCode() == 0) //already install or install
    {
        cleanup(package.isCask());
        return 0;
    }
    else //error
    {
        return -1;
    }

}


int uninstall(PackageDTO package)
{
    QString command = "/usr/local/bin/brew ";
    command.append(package.isCask() ? "cask uninstall " : "uninstall ");
    command.append(package.filename());

    QProcess process;
    process.start(command);
    process.waitForFinished(-1); // will wait forever until finished

    if (process.exitCode() == 0)
    {
        return 0;
    }
    else
    {
        //error
        return -1;
    }
}

void cleanup(bool cask)
{
    QString command = "/usr/local/bin/brew ";
    command += cask ? "cask cleanup" : "cleanup";
    QProcess process;
    process.start(command);
}

QStringList list(bool isCask)
{
    if (isCask)
    {
        return listArgument("cask list -1"); //brew cask installed
    }
    else
    {
        return listArgument("list -1"); //brew installed
    }
}

QStringList listArgument(QString argument)
{
    QProcess process;
    process.start("/usr/local/bin/brew " + argument);
    process.waitForFinished(-1); // will wait forever until finished
    QString standardOutput = process.readAllStandardOutput();
    return standardOutput.split("\n");
}

void createDB(bool cask)
{
    QDir currentDir(getBrewPath(cask));
    QDirIterator it(currentDir);
    while (it.hasNext())
    {
        it.next();
        if (it.fileInfo().isFile())
        {
            QMap<QString, QString> map (infoPackage(it.fileInfo().baseName(), cask));
            PackageDTO package {map.value("filename"), map.value("name"), map.value("version"),
                                map.value("homepage"), map.value("url"), map.value("desc"),
                                cask, false, false};
            addPackage(package); //add the new package to the DB
        }
    }
}

QMap<QString, QString> infoPackage(QString filename, bool cask)
{
    QMap<QString, QString> map;
    QStringList infos (QStringList() << "  version " << "  url "
                       << "  name " << "  homepage "  << "  desc ");
    map.insert("filename", filename);
    map.insert("name", "");
    map.insert("version", "");
    map.insert("url", "");
    map.insert("desc", "");
    map.insert("homepage", "");
    QString path = getBrewPath(cask) + filename + ".rb";
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd() && !infos.isEmpty())
        {
            QString line = in.readLine();
            addToMap(map, infos, line);

        }
        inputFile.close();
    }
    return map;
}

void addToMap(QMap<QString, QString> & map, QStringList & infos, QString line)
{
    for (QString info : infos)
    {
        if (line.indexOf(info) != -1)
        {
            line.remove(QRegExp("'|\"|:"));
            QStringList items = line.split(" ", QString::SkipEmptyParts);
            QString key (items.at(0));
            QString value (items.at(1));
            if (info == "  name " || info == "  desc ")
            {
                for (int i = 2 ; i < items.size() ; i++)
                {
                    value.append(" " + items.at(i));
                }
            }
            map.insert(key, value);
            infos.removeOne(info);
            return;
        }
    }
}

void updateHomebrew()
{
    QProcess process;
    process.start("/usr/local/bin/brew update");
    process.waitForFinished(-1);
}


} //namespace qbrew
