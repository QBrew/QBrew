#include "process.h"
#include <sstream>
#include <iostream>
#include <QProcess>

bool qbrew::isBrewCaskInstalled()
{
    QProcess process;
    QString str = "/usr/local/bin/brew --version ";
    process.start(str);
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();

    return !stdout.isEmpty();
}

std::pair<std::string, std::string> qbrew::brewVersion()
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

    std::pair<std::string, std::string> versions(versionBrew, versionBrewCask);
}

std::vector<std::string> qbrew::search(std::string search, bool cask)
{
    QProcess process;
    std::string str = "/usr/local/bin/brew ";
    str += cask ? "cask search " : "search ";
    str += search;
    process.start(QString::fromStdString(str));
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();

    std::vector<std::string> results;
    std::stringstream  stream;
    stream.str(stdout.toStdString());
    std::string line;
    while (std::getline(stream, line))
    {
        if (!line.compare("==> Partial matches") == 0 &&
                !line.compare("==> Exact match") == 0)
        {
            results.push_back(line);
        }
    }

    return results;
}

int qbrew::install(std::string package, bool cask)
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

    return 0;

}
