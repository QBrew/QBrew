#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>

class navigationBar : public QWidget
{
    Q_OBJECT

    void setButtons();
    void setGroup();

  public:
    explicit navigationBar(QWidget * parent = 0);
    QPushButton * all();
    QPushButton * installed();
    QPushButton * favourite();

  signals:

  public slots:

  private:
    QButtonGroup * group_;
    QPushButton * all_;
    QPushButton * installed_;
    QPushButton * favourite_;
    QVBoxLayout * vBox_;
};

#endif // NAVIGATIONBAR_H
