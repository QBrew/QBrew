#include "menubar.h"

#include "../db/db/dbactions.h"
#include "../db/DTO/packagedto.h"

#include <QMessageBox>
#include <QTextStream>

namespace qbrewview
{

MenuBar::MenuBar(QWidget * parent, PackageList * list) : QMenuBar(parent)
{
    menu_ = new QMenu();
    addMenu(menu_);

    favourites_ = new QMenu("Favourites");
    addMenu(favourites_);

    setActions();
    setConnections();

    list_ = list;
}

void MenuBar::setActions()
{
    aboutAction_ = menu_->addAction(tr("About"));
    preferencesAction_    = menu_->addAction(tr("Preferences"));

    importFavourites_ = favourites_->addAction(tr("Import"));
    exportFavourites_ = favourites_->addAction(tr("Export"));
}

void MenuBar::setConnections()
{
    connect(aboutAction_,    &QAction::triggered, this, &MenuBar::aboutPopup);
    connect(preferencesAction_,    &QAction::triggered, this,
            &MenuBar::preferencesPopup);

    connect(importFavourites_, &QAction::triggered, this, &MenuBar::importPopup);
    connect(exportFavourites_, &QAction::triggered, this, &MenuBar::exportPopup);
}

void MenuBar::aboutPopup()
{
    About * popup = new About(this);
    popup->exec();
}

void MenuBar::preferencesPopup()
{
    Preferences * popup = new Preferences(this);
    popup->exec();
}

void MenuBar::importPopup()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Import Favourites"),
                   QDir::homePath());
    if (path == "")
    {
        return;
    }

    QMessageBox::StandardButton merge;
    merge = QMessageBox::question(this, "",
                                  "Do you want to delete your current favourite list ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (merge == QMessageBox::Yes)
    {
        removeAllFavourites();
    }

    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QStringList s = in.readLine().split(" ");
            addFavourite(s.at(0), s.at(1) == "1");
        }
        file.close();
        list_->update();
    }
}

void MenuBar::exportPopup()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Export Favourites"),
                   QDir::homePath() + "/fav.qbrew");
    if (path == "")
    {
        return;
    }
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    for (PackageDTO p : getFavourites())
    {
        out << p.filename() << " ";
        out << QString::number(p.isCask() ? 1 : 0) << "\n";
    }
    file.close();
}

}
