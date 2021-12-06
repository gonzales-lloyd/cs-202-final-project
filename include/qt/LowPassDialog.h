#include <QDialog>
#include <QDebug>
#include <QString>
#include "ui_lowpass.h"

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click

#ifndef LOWPASSDIALOG_H
#define LOWPASSDIALOG_H

class LowPassDialog : public QDialog, public Ui_LowPassDialog{
    Q_OBJECT

public:
    LowPassDialog(QWidget*parent = 0);
private slots:
    /**
     * @brief Slot to open filepath dialog when the path dialog button is clicked.
     */
    void on_pathDialogButton_clicked();
    /**
     * @brief Slot to ensure window closes on rejection.
     */
    void on_LowPassDialog_rejected();
};

#endif // LOWPASSDIALOG_H
