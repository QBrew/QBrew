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
#include <QLineEdit>
#include <QSettings>

class preferences : public QDialog
{
    Q_OBJECT
public:
    preferences(QWidget* Parent);
    void setTextZone();
    void setButtons();

signals:

public slots:
    void save();
    void getDirectory();

private :
    QVBoxLayout* vbox_;
    QLineEdit* path_;
    QPushButton* closeButton_;
    QPushButton* saveButton_;
    QPushButton* pathButton_;
};

#endif // PREFERENCES_H
