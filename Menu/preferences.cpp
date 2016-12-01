#include "preferences.h"

preferences::preferences(QWidget* parent) : QDialog(parent)
{
    vbox_ = new QVBoxLayout;
    setWindowTitle("Preferences");
    setTextZone();
    setButtons();
    setLayout(vbox_);
    layout()->setSizeConstraint( QLayout::SetFixedSize ) ;
    setSizeGripEnabled( false ) ;
}

void preferences::setTextZone(){
    QLabel* title = new QLabel("Path : ");
    vbox_->addWidget(title,Qt::AlignLeft);

    QHBoxLayout* hbox = new QHBoxLayout;

    QFile file(":/path.txt");
    file.open(QIODevice::ReadOnly);
    QString text = file.readLine();
    path_ = new QTextEdit(text);
    path_->setMaximumSize(300,20);
    hbox->addWidget(path_);
    pathButton_ = new QPushButton("...");
    hbox->addWidget(pathButton_);

    vbox_->addLayout(hbox);
}

void preferences::setButtons(){
    QHBoxLayout* hbox = new QHBoxLayout;

    closeButton_ = new QPushButton("Close");
    closeButton_->setMinimumSize(75,30);
    closeButton_->setMaximumSize(75,30);
    connect(closeButton_, SIGNAL (clicked()),this,SLOT(close()));
    hbox->addWidget(closeButton_);
    //vbox_->setAlignment(closeButton_,Qt::AlignRight);

    saveButton_ = new QPushButton("Ok");
    saveButton_->setMinimumSize(75,30);
    saveButton_->setMaximumSize(75,30);
    //connect(closeButton_, SIGNAL (clicked()),this,SLOT(close()));
    hbox->addWidget(saveButton_);
    //vbox_->setAlignment(closeButton_,Qt::AlignRight);

    vbox_->addLayout(hbox);
}
