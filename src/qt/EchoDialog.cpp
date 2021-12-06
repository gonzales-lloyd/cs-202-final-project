#include "EchoDialog.h"

#include <QFileDialog>

EchoDialog::EchoDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void EchoDialog::on_pathDialogButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Save output as..."), QDir::currentPath(), tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}
