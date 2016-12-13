#include "navigationbar.h"

#include <QButtonGroup>


navigationBar::navigationBar(QWidget * parent) : QWidget(parent)
{
    setButtons();
    setGroup();
    this->setLayout(vBox_);
}

QPushButton * navigationBar::all()
{
    return all_;
}

QPushButton * navigationBar::installed()
{
    return installed_;
}

QPushButton * navigationBar::favourite()
{
    return favourite_;
}

void navigationBar::setButtons()
{
    group_ = new QButtonGroup(this);
    vBox_ = new QVBoxLayout();
    vBox_->setContentsMargins(0, 0, 0, 0);
    vBox_->setSpacing(10);
    vBox_->setAlignment(Qt::AlignTop);

    QString style =
        "QPushButton{ "
        "text-align: left;"
        "color:black;"
        "font-size: 14pt;"
        "border-style:raised;"
        "width: 160px;"
        "height: 20px;"
        "padding: 10px;}"

        "QPushButton:checked {"
        "background-color:#CECECE;}";

    all_ = new QPushButton(tr("All"));
    all_->setCheckable(true);
    all_->setChecked(true);
    all_->setStyleSheet(style);

    installed_ = new QPushButton(tr("Installed"));
    installed_->setCheckable(true);
    installed_->setStyleSheet(style);

    favourite_ = new QPushButton(tr("Favourite"));
    favourite_->setCheckable(true);
    favourite_->setStyleSheet(style);

    vBox_->addWidget(all_);
    vBox_->addWidget(installed_);
    vBox_->addWidget(favourite_);
}

void navigationBar::setGroup()
{
    group_->addButton(all_);
    group_->addButton(installed_);
    group_->addButton(favourite_);
    group_->setExclusive(true);
}
