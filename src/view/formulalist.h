#ifndef FORMULALIST_H
#define FORMULALIST_H

#include <QTableWidget>
#include <QCheckBox>
#include <QList>
#include <src/db/DTO/formuladto.h>

class FormulaList : public QTableWidget
{
    Q_OBJECT

    QList<qbrew::FormulaDTO> formula_;
    QList<QCheckBox *> checkBoxes_;

  public:
    explicit FormulaList(QWidget * parent = 0);
    void setAll();
    void setFavorite();
    void setInstalled();
    void search(QString searchValue);

    void selectFormula(bool isAll);
    QList<qbrew::FormulaDTO> getSelected();

    void tableItemClicked(int row, int column);
    void tableItemDoubleClicked(int row, int column);
  private:
    void setList();
  signals:

  public slots:

};

#endif // FORMULALIST_H
