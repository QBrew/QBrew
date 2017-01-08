#include "infobar.h"

#include <QVBoxLayout>

namespace qbrewview
{

InfoBar::InfoBar(QWidget * parent) : QWidget(parent)
{
    initialize();
    QVBoxLayout * vBox = new QVBoxLayout();

    QHBoxLayout * hBoxName = hBoxCreator("Name :");
    hBoxName->addWidget(name_);
    vBox->addLayout(hBoxName);

    QHBoxLayout * hBoxFilename = hBoxCreator("Filename : ");
    hBoxFilename->addWidget(filename_);
    vBox->addLayout(hBoxFilename);

    QHBoxLayout * hBoxVersion = hBoxCreator("Version :");
    hBoxVersion->addWidget(version_);
    vBox->addLayout(hBoxVersion);

    QHBoxLayout * hBoxDesc = hBoxCreator("Description :");
    hBoxDesc->addWidget(desc_);
    vBox->addLayout(hBoxDesc);

    QHBoxLayout * hBoxHomepage = hBoxCreator("Homepage :");
    hBoxHomepage->addWidget(homepage_);
    vBox->addLayout(hBoxHomepage);

    QHBoxLayout * hBoxUrl = hBoxCreator("Url :");
    hBoxUrl->addWidget(url_);
    vBox->addLayout(hBoxUrl);

    this->setLayout(vBox);
}

void InfoBar::updateInfo(PackageDTO package)
{
    filename_->setText(package.filename());
    name_->setText(package.name());
    version_->setText(package.version());
    homepage_->setText(package.homepage());
    url_->setText(package.url());
    desc_->setText(package.desc());

}

QHBoxLayout * InfoBar::hBoxCreator(QString text)
{
    QHBoxLayout * hBox = new QHBoxLayout();
    hBox->setAlignment(Qt::AlignLeft);
    QLabel * label = new QLabel(text);
    hBox->addWidget(label);
    return hBox;
}

void InfoBar::initialize()
{
    name_ = new QLabel();
    filename_ = new QLabel();
    version_ = new QLabel();
    url_ = new QLabel();
    homepage_ = new QLabel();
    desc_ = new QLabel();
}

void InfoBar::clear()
{
    name_->clear();
    filename_->clear();
    version_->clear();
    url_->clear();
    homepage_->clear();
    desc_->clear();
}

}
