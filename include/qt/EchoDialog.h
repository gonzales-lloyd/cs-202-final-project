#include <QDialog>
#include <QDebug>
#include <QString>
#include "ui_echo.h"

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click

#ifndef ECHODIALOG_H
#define ECHODIALOG_H

class EchoDialog : public QDialog, public Ui_EchoDialog{
    Q_OBJECT

public:
    EchoDialog(QWidget*parent = 0);
private slots:
    void on_pathDialogButton_clicked();
    void on_EchoDialog_rejected();
};

#endif // EchoDIALOG_H
