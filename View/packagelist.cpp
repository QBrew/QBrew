#include "packagelist.h"
#include "packagemodel.h"
#include "Process/process.h"

#include <QHeaderView>
#include <QFile>
#include <QDebug>

#include <QFileInfoList>
/*void packageList::setHeaderLabels()
{
    QStringList headerLabels
    {
        tr(""),
        tr(""),
        tr("Name"),
        tr("Version")
    };

    QStandardItemModel * model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(headerLabels);

    setModel(model);

    setSortingEnabled(true);
    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}*/

void packageList::setTreeView()
{
    QString data;
    //QStringList search = qbrew::search2("", true);
    QFileInfoList search = qbrew::search2("", true);
    for (auto test : search)
    {
        QMap<std::string, std::string> map = qbrew::infoPackage(
                test.baseName().toStdString(),
                true);
        data += "1\t" + QString::fromStdString(map["name"]) + "\t" +
                QString::fromStdString(map["version"]) + "\n";
    }


    /*QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray test = file.readAll();
    QString test2 = (QString)test;
    qDebug() << "test " << test2.split(QString("\n"));*/
    packageModel * model = new packageModel(data);

    //file.close();
    /*QStandardItem * check;
    QStandardItem * favori;
    QStandardItem * name;
    QStandardItem * version;

    for (std::string test : qbrew::list(false))
    {

        check = new QStandardItem();
        favori = new QStandardItem();
        name = new QStandardItem(QString::fromStdString(test));
        version = new QStandardItem(QString::fromStdString(
                                        qbrew::infoPackage(test,
                                                false).at("version")));

        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        version->setFlags(version->flags() & ~Qt::ItemIsEditable);

        model->appendRow(QList<QStandardItem *>() << check << favori << name <<
        version);
    }

        model->setHorizontalHeaderItem(0, new QStandardItem());
     model->setHorizontalHeaderItem(1, new QStandardItem());
     model->setHorizontalHeaderItem(2, new QStandardItem(QString("Name")));
     model->setHorizontalHeaderItem(3, new QStandardItem(QString("Version")));*/

    header()->setSectionResizeMode(QHeaderView::ResizeToContents);



    setAlternatingRowColors(true);
    setModel(model);
}

packageList::packageList(QWidget * parent) : QTreeView(parent)
{
    setTreeView();
}
