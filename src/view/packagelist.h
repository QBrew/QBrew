#ifndef PACKAGELIST_H
#define PACKAGELIST_H

#include <QTableWidget>
#include <QCheckBox>
#include <QList>
#include <src/db/DTO/packagedto.h>

namespace qbrew
{

class PackageList : public QTableWidget
{
    Q_OBJECT

    QList<PackageDTO> packages_;
    QList<QCheckBox *> checkBoxes_;

  public:
    explicit PackageList(QWidget * parent = 0);
    void setAll();
    void setFavorite();
    void setInstalled();
    void search(QString searchValue);

    void selectPackage(bool isAll);
    QList<PackageDTO> getSelectedFavorite();

    void tableItemClicked(int row, int column);
    void tableItemDoubleClicked(int row, int column);
  private:
    void setList();
  signals:

  public slots:

};

}

#endif // PACKAGELIST_H
