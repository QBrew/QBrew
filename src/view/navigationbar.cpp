#include "navigationbar.h"

#include <QButtonGroup>

NavigationBar::NavigationBar(QWidget * parent) : QWidget(parent)
{
    setButtons();
    this->setLayout(vBox_);
}

void NavigationBar::setButtons()
{
    group_ = new QButtonGroup(this);
    group_->setExclusive(true);
    vBox_ = new QVBoxLayout();
    vBox_->setContentsMargins(0, 0, 0, 0);
    vBox_->setSpacing(10);
    vBox_->setAlignment(Qt::AlignTop);

    all_ = getPushButton(tr("All"));
    installed_ = getPushButton(tr("Installed"));
    favourite_ = getPushButton(tr("Favourite"));
    favourite_->setChecked(true);
    search_ = getPushButton(tr("Search"));

    vBox_->addWidget(all_);
    vBox_->addWidget(installed_);
    vBox_->addWidget(favourite_);
    vBox_->addWidget(search_);
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
