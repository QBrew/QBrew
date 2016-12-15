#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class About : public QDialog
{
  public:
    About(QWidget * parent);
    void setText();
    void setButton();

  signals:

  public slots:

  private:
    QVBoxLayout * vbox_;
    QLabel * text_;
    QPushButton * closeButton_;
};

#endif // ABOUT_H
