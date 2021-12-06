#include "LowPassDialog.h"

#include <QFileDialog>

LowPassDialog::LowPassDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void LowPassDialog::on_pathDialogButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Save output as..."), QDir::currentPath(), tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void LowPassDialog::on_LowPassDialog_rejected()
{
    this->close();
}

