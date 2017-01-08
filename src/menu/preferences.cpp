#include "preferences.h"

namespace qbrewview
{

Preferences::Preferences(QWidget * parent) : QDialog(parent)
{
    vbox_ = new QVBoxLayout;
    setWindowTitle("Preferences");
    setTextZone();
    setButtons();
    setLayout(vbox_);
    layout()->setSizeConstraint( QLayout::SetFixedSize ) ;
    setSizeGripEnabled( false ) ;
}

void Preferences::setTextZone()
{
    QLabel * title = new QLabel("Path : ");
    vbox_->addWidget(title, Qt::AlignLeft);

    QHBoxLayout * hbox = new QHBoxLayout;

    QSettings settings("Projet", "QBrew");
    QString text = settings.value("path").toString();

    path_ = new QLineEdit(text);
    path_->setMinimumSize(300, 20);
    path_->setMaximumSize(300, 20);
    hbox->addWidget(path_);
    pathButton_ = new QPushButton("...");
    hbox->addWidget(pathButton_);

    vbox_->addLayout(hbox);
}

void Preferences::setButtons()
{
    QHBoxLayout * hbox = new QHBoxLayout;

    closeButton_ = new QPushButton("Cancel");
    closeButton_->setMinimumSize(75, 30);
    closeButton_->setMaximumSize(75, 30);
    connect(closeButton_, SIGNAL (clicked()), this, SLOT(close()));
    hbox->addWidget(closeButton_);

    saveButton_ = new QPushButton("Ok");
    saveButton_->setMinimumSize(75, 30);
    saveButton_->setMaximumSize(75, 30);
    connect(saveButton_, SIGNAL (clicked()), this, SLOT(save()));
    hbox->addWidget(saveButton_);

    connect(pathButton_, SIGNAL (clicked()), this, SLOT(getDirectory()));

    vbox_->addLayout(hbox);
}


void Preferences::save()
{
    QSettings settings("Projet", "QBrew");
    settings.setValue("path", path_->text());
    this->close();
}

void Preferences::getDirectory()
{
    QString dir;
    if (QDir(path_->text()).exists())
    {
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                path_->text(),
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    }
    else
    {
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    }
    if (!dir.isEmpty() && !dir.isNull())
    {
        path_->setText(dir);
    }
}

}
