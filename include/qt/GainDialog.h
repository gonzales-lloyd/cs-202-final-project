#include <QDialog>
#include <QDebug>
#include <QString>
#include "ui_gain.h"

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click

#ifndef GAINDIALOG_H
#define GAINDIALOG_H

class GainDialog : public QDialog, public Ui_GainDialog{
    Q_OBJECT

public:
    GainDialog(QWidget*parent = 0);
private slots:
    void on_pathDialogButton_clicked();
};

#endif // GAINDIALOG_H
