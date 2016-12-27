#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>
#include <QAction>
#include <QPushButton>
#include <QVBoxLayout>

class NavigationBar : public QWidget
{
    Q_OBJECT

    void setButtons();

  public:
    explicit NavigationBar(QWidget * parent = 0);

    inline QPushButton * installed();
    inline QPushButton * favourite();
    inline QPushButton * search();

  signals:

  public slots:

  private:
    QButtonGroup * group_;
    QPushButton * installed_;
    QPushButton * favourite_;
    QPushButton * search_;
    QVBoxLayout * vBox_;

    QPushButton * getPushButton(const QString & name);
};


QPushButton * NavigationBar::installed()
{
    return installed_;
}

QPushButton * NavigationBar::favourite()
{
    return favourite_;
}

QPushButton * NavigationBar::search()
{
    return search_;
}


#endif // NAVIGATIONBAR_H
