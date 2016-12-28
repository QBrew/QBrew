#ifndef INFOBAR_H
#define INFOBAR_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "src/db/DTO/packagedto.h"

class infoBar : public QWidget
{
    Q_OBJECT
  public:
    explicit infoBar(QWidget * parent = 0);

    void updateInfo(qbrew::PackageDTO package);

    void initialize();
    QHBoxLayout * hBoxCreator(QString text);

  signals:

  public slots:

  private:
    QLabel * name_;
    QLabel * filename_;
    QLabel * version_;
    QLabel * url_;
    QLabel * homepage_;
    QLabel * desc_;
};

#endif // INFOBAR_H
