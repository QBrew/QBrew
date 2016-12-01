#include "process.h"
#include <sstream>
#include <iostream>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include <QDebug>

namespace qbrew
{



QString getBrewPath(bool isCask)
{
    //TODO check if path is no default

    QString path = isCask ?
                   "/usr/local/Homebrew/Library/Taps/caskroom/homebrew-cask/Casks/" :
                   "/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/";
    return path;
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

std::pair<std::string, std::string> brewVersion()
{
    QProcess process;
    QString str = "/usr/local/bin/brew --version ";
    process.start(str);
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();
    std::string strout = stdout.toStdString();
    std::size_t pos = strout.find("\n");
    std::string versionBrew = strout.substr (9, pos - 9);

    str = "/usr/local/bin/brew cask --version ";
    process.start(str);
    process.waitForFinished(-1); // will wait forever until finished
    stdout = process.readAllStandardOutput();
    strout = stdout.toStdString();
    pos = strout.find("\n");
    std::string versionBrewCask = strout.substr (14, pos - 14);

    std::pair<std::string, std::string> versions(versionBrew,
            versionBrewCask);

    return versions;
}

QPair<QString, QString> brewVersion2()
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

std::vector<std::string> search(std::string search, bool isCask)
{
    std::string argument = isCask ? "cask search " : "search ";
    argument += search;
    std::vector<std::string> results = listArgument(argument);
    results.erase(std::remove(results.begin(), results.end(),
                              "==> Partial matches"), results.end());
    results.erase(std::remove(results.begin(), results.end(), "==> Exact match"),
                  results.end());

    return results;
}


QFileInfoList search2(QString searchValue, bool isCask)
{
    QDir currentDir(getBrewPath(isCask));
    searchValue = searchValue.isEmpty() ? "*"  : "*" + searchValue + "*";
    QFileInfoList files = currentDir.entryInfoList(QStringList(searchValue),
                          QDir::Files);
    return files;
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

QMap<std::string, std::string> infoPackage(std::string package, bool isCask)
{
    QMap<std::string, std::string> map;
    map["name"] = package;
    map["version"] = "";
    map["desc"] = "";
    map["url"] = "";
    map["homepage"] = "";
    QString path = isCask ?
                   "/usr/local/Homebrew/Library/Taps/caskroom/homebrew-cask/Casks/" :
                   "/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/";
    path += QString::fromStdString(package) + ".rb";
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        QList<std::string> infos = {"  desc ", "  homepage ", "  url ", "  version ", "  name "};
        QTextStream in(&file);
        while (!in.atEnd())
        {
            std::string line = in.readLine().toStdString();
            for (std::string info : infos)
            {
                if (line.find(info) != std::string::npos)
                {
                    line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
                    line.erase(std::remove(line.begin(), line.end(), '\''), line.end());
                    line.erase(std::remove(line.begin(), line.end(), ':'), line.end());
                    map[info.substr(2, info.length() - 3)] = line.substr(info.length(),
                            line.length() - info.length());
                    infos.removeOne(info);
                    break;
                }
            }
        }
        file.close();
    }
    return map;
}



} //namespace qbrew
