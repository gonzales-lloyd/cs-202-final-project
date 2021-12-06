#include "EchoDialog.h"

#include <QFileDialog>

EchoDialog::EchoDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void EchoDialog::on_pathDialogButton_clicked()
{
    auto openDir = QDir::currentPath();
    if(!this->outputPath->text().isEmpty()){
        openDir = this->outputPath->text();
    }
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Load WAV file..."), openDir, tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void EchoDialog::on_EchoDialog_rejected()
{
    this->close();
}

