#include "infobar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

infoBar::infoBar(QWidget * parent) : QWidget(parent)
{
    QVBoxLayout * vBox = new QVBoxLayout();

    QHBoxLayout * hBoxName = new QHBoxLayout();
    QLabel * name = new QLabel("Name :");
    hBoxName->addWidget(name);
    name_ = new QLabel();
    hBoxName->addWidget(name_);
    vBox->addLayout(hBoxName);

    QHBoxLayout * hBoxFilename = new QHBoxLayout();
    QLabel * filename = new QLabel("Filename : ");
    hBoxFilename->addWidget(filename);
    filename_ = new QLabel();
    hBoxFilename->addWidget(filename_);
    vBox->addLayout(hBoxFilename);

    QHBoxLayout * hBoxVersion = new QHBoxLayout();
    QLabel * version = new QLabel("Version :");
    hBoxVersion->addWidget(version);
    version_ = new QLabel();
    hBoxVersion->addWidget(version_);
    vBox->addLayout(hBoxVersion);

    QHBoxLayout * hBoxDesc = new QHBoxLayout();
    QLabel * desc = new QLabel("Description :");
    hBoxDesc->addWidget(desc);
    desc_ = new QLabel();
    hBoxDesc->addWidget(desc_);
    vBox->addLayout(hBoxDesc);

    QHBoxLayout * hBoxHomepage = new QHBoxLayout();
    QLabel * homepage = new QLabel("Homepage :");
    hBoxHomepage->addWidget(homepage);
    homepage_ = new QLabel();
    hBoxHomepage->addWidget(homepage_);
    vBox->addLayout(hBoxHomepage);

    QHBoxLayout * hBoxUrl = new QHBoxLayout();
    QLabel * url = new QLabel("Url :");
    hBoxUrl->addWidget(url);
    url_ = new QLabel();
    hBoxUrl->addWidget(url_);
    vBox->addLayout(hBoxUrl);

    this->setLayout(vBox);
}

void infoBar::updateInfo(qbrew::PackageDTO package)
{
    filename_->setText(package.filename());
    name_->setText(package.name());
    version_->setText(package.version());
    homepage_->setText(package.homepage());
    url_->setText(package.url());
    desc_->setText(package.desc());

}
