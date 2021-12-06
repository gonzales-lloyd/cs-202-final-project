#include "LowPassDialog.h"

#include <QFileDialog>

LowPassDialog::LowPassDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void LowPassDialog::on_pathDialogButton_clicked()
{
    auto openDir = QDir::currentPath();
    if(!this->outputPath->text().isEmpty()){
        openDir = this->outputPath->text();
    }
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Load WAV file..."), openDir, tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void LowPassDialog::on_LowPassDialog_rejected()
{
    this->close();
}

