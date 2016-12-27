#include "process.h"
#include <sstream>
#include <iostream>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include "../db/dto/formuladto.h"
#include "../db/db/qbrewdb.h"

#include <QDebug>

namespace qbrew
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

int install(std::string package, bool cask)
{
    QProcess process;
    std::string str = "/usr/local/bin/brew ";
    str += cask ? "cask install " : "install ";
    str += package;
    process.start(QString::fromStdString(str));
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    //if no matching package
    if (stderr.toStdString().find("No available") != std::string::npos)
    {
        return -1;
    }

    //if already installed
    if (stderr.toStdString().find("already installed") != std::string::npos)
    {
        return -2;
    }

    //if connection problems
    if (stderr.toStdString().find("failed") != std::string::npos)
    {
        return -3;
    }

    //install well done
    str = "/usr/local/bin/brew ";
    str += cask ? "cask cleanup" : "cleanup";
    process.start(QString::fromStdString(str));
    return 0;
}

int install(QString package, bool cask)
{
    QProcess process;
    QString command = "/usr/local/bin/brew ";
    command.append(cask ? "cask install " : "install " + package);
    process.start(command);
    process.waitForFinished(-1); // will wait forever until finished

    if (process.exitCode() == 0)
    {
        //already install or install
        cleanup(cask);
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

QStringList list()
{
    QStringList result = listArgument("cask list -1");
    result.append(listArgument("list -1"));
    return result;
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
    QList<QMap<QString, QString>> maps;
    QDir currentDir(getBrewPath(cask));
    QDirIterator it(currentDir);
    while (it.hasNext())
    {
        it.next();
        if (it.fileInfo().isFile())
        {
            QMap<QString, QString> map (infoPackage(it.fileInfo().baseName(), true));
            FormulaDTO formula {map.value("filename"), map.value("name"), map.value("version"),
                                map.value("homepage"), map.value("url"), map.value("desc")};
            addFormula(formula);
        }

    }
}

QMap<QString, QString> infoPackage(QString filename, bool cask)
{
    QMap<QString, QString> map;
    QStringList infos (QStringList() << "  version " << "  url "
                       << "  name " );//<< "  homepage "  << "  desc ");
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
            line.remove('"');
            line.remove('\'');
            line.remove(':');
            QStringList items = line.split(" ", QString::SkipEmptyParts);
            QString key (items.at(0));
            QString value (items.at(1));
            if (info == "  name ")
            {
                for (int i = 2 ; i < items.size() ; i++)
                {
                    value.append(" " + items.at(i));
                }
            }
            map.insert(key, value);
            infos.removeOne(info);
            break;
        }
    }
}



} //namespace qbrew
