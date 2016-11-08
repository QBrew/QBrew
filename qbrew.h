#ifndef QBREW_H
#define QBREW_H

#include <QMainWindow>

namespace Ui {
class QBrew;
}

class QBrew : public QMainWindow
{
    Q_OBJECT

public:
    explicit QBrew(QWidget *parent = 0);
    ~QBrew();

private:
    Ui::QBrew *ui;
};

#endif // QBREW_H
