#include <QDialog>
#include <QDebug>
#include <QString>
#include "ui_normalization.h"

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click

#ifndef NORMALIZATIONDIALOG_H
#define NORMALIZATIONDIALOG_H

class NormalizationDialog : public QDialog, public Ui_NormalizationDialog{
    Q_OBJECT

public:
    NormalizationDialog(QWidget*parent = 0);
private slots:
    void on_pathDialogButton_clicked();
};

#endif // NORMALIZATIONDIALOG_H
