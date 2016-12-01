#include "about.h"

about::about(QWidget * parent) : QDialog(parent)
{
    vbox_ = new QVBoxLayout;
    setWindowTitle("About");
    setText();
    setButton();
    setLayout(vbox_);
    layout()->setSizeConstraint( QLayout::SetFixedSize ) ;
    setSizeGripEnabled( false ) ;
}

void about::setText()
{
    text_ = new QLabel("QBrew\n"
                       "Licence : GPL3 (https://www.gnu.org/licenses/gpl-3.0.txt)\n"
                       "By :\n"
                       "Cédric Gilon\n"
                       "Arnaud De Bruecker\n"
                       "Quentin Ravau");
    vbox_->addWidget(text_);
}

void about::setButton()
{
    closeButton_ = new QPushButton("Close");
    closeButton_->setMinimumSize(75, 30);
    closeButton_->setMaximumSize(75, 30);
    connect(closeButton_, SIGNAL (clicked()), this, SLOT(close()));
    vbox_->addWidget(closeButton_);
    vbox_->setAlignment(closeButton_, Qt::AlignRight);
}
