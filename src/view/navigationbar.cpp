#include "navigationbar.h"
#include "src/db/DB/dbactions.h"

#include <QButtonGroup>

namespace qbrewview
{

NavigationBar::NavigationBar(QWidget * parent) : QWidget(parent)
{
    setButtons();
    this->setLayout(vBox_);
}

void NavigationBar::updateNumber()
{
    installed_->setText("Installed(" + QString::number(qbrewdb::numberInstalled()) +
                        ")");
    favourite_->setText("Favourite(" + QString::number(qbrewdb::numberFavourite()) +
                        ")");
}

void NavigationBar::setButtons()
{
    group_ = new QButtonGroup(this);
    group_->setExclusive(true);
    vBox_ = new QVBoxLayout();
    vBox_->setContentsMargins(0, 0, 0, 0);
    vBox_->setSpacing(10);
    vBox_->setAlignment(Qt::AlignTop);

    installed_ = getPushButton("Installed(" + QString::number(
                                   qbrewdb::numberInstalled()) +
                               ")");
    favourite_ = getPushButton("Favourite(" + QString::number(
                                   qbrewdb::numberFavourite()) +
                               ")");

    installed_->setChecked(true);

    vBox_->addWidget(installed_);
    vBox_->addWidget(favourite_);
}

QPushButton * NavigationBar::getPushButton(const QString & name)
{
    QString style =
        "QPushButton{ "
        "text-align: left;"
        "color:black;"
        "font-size: 14pt;"
        "border-style:raised;"
        "width: 191px;"
        "height: 20px;"
        "padding: 10px;}"

        "QPushButton:checked {"
        "background-color:#CECECE;}";

    QPushButton * qpb = new QPushButton(name);
    qpb->setCheckable(true);
    qpb->setStyleSheet(style);
    group_->addButton(qpb);
    return qpb;
}

}
