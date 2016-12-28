#ifndef PACKAGELIST_H
#define PACKAGELIST_H

#include <QTableWidget>
#include <QCheckBox>
#include <QList>
#include <QIcon>
#include <src/db/DTO/packagedto.h>

namespace qbrew
{

class PackageList : public QTableWidget
{
    Q_OBJECT

    QString status_;

    QList<PackageDTO> packages_;
    QList<QCheckBox *> checkBoxes_;
    QIcon favouriteIcon_;
    QIcon noFavouriteIcon_;
    QList<QIcon> statusIcons_;
    int row_;


  public:
    explicit PackageList(QWidget * parent = 0);
    void setFavorite();
    void setInstalled();
    void setIcons();
    PackageDTO getSelected();
    PackageDTO getPackage(int row);
    void setSearch(QString searchValue);

    void update();

    void selectPackage(bool isAll);
    QList<PackageDTO> getListSelected();

    void tableItemClicked(int row, int column);
    void tableItemDoubleClicked(int row, int column);
    QString getStatus() const;

  private:
    void setList();
    QWidget * alignCheckBox(QCheckBox * cb);
  signals:
    void clickedItemChange();

  public slots:

};

}

#endif // PACKAGELIST_H
