#include "qbrew.h"
#include "ui_qbrew.h"

QBrew::QBrew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QBrew)
{
    ui->setupUi(this);
}

QBrew::~QBrew()
{
    delete ui;
}
