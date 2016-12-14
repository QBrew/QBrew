#include "process.h"
#include <sstream>
#include <iostream>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include "../DB/DTO/formuladto.h"
#include "../DB/DB/qbrewdb.h"

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

std::vector<std::string> listArgument(std::string argument)
{
    QProcess process;
    std::string str = "/usr/local/bin/brew " + argument;

    process.start(QString::fromStdString(str));
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();

    std::vector<std::string> results;
    std::stringstream  stream;
    stream.str(stdout.toStdString());
    std::string line;
    while (std::getline(stream, line))
    {
        results.push_back(line);
    }

    return results;
}

std::vector<std::string> list(bool isCask)
{
    return listArgument(isCask ? "cask list" : "list");
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
            FormulaDTO formula {map.value("name"), map.value("version"),
                                map.value("homepage"), map.value("url"),
                                map.value("desc")};
            addFormula(formula);
        }

    }
}

QMap<QString, QString> infoPackage(QString filename, bool cask)
{
    QMap<QString, QString> map;
    QStringList infos (QStringList() << "  version " << "  url "
                       << "  name " );//<< "  homepage "  << "  desc ");
    map.insert("name", filename);
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
