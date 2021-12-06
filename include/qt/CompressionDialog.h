#include <QDialog>
#include <QDebug>
#include <QString>
#include "ui_compression.h"

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click

#ifndef COMPRESSIONDIALOG_H
#define COMPRESSIONDIALOG_H

class CompressionDialog : public QDialog, public Ui_CompressionDialog{
    Q_OBJECT

public:
    CompressionDialog(QWidget*parent = 0);
private slots:
    void on_pathDialogButton_clicked();
    void on_CompressionDialog_rejected();
};

#endif // COMPRESSIONDIALOG_H
