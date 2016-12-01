#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <iostream>
#include <QFile>

class preferences : public QDialog
{
public:
    preferences(QWidget* Parent);
    void setTextZone();
    void setButtons();

signals:

public slots:
    //void save();

private :
    QVBoxLayout* vbox_;
    QTextEdit* path_;
    QPushButton* closeButton_;
    QPushButton* saveButton_;
    QPushButton* pathButton_;
};

#endif // PREFERENCES_H
