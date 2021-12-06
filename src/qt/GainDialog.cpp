#include "GainDialog.h"

#include <QFileDialog>

GainDialog::GainDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void GainDialog::on_pathDialogButton_clicked()
{
    auto openDir = QDir::currentPath();
    if(!this->outputPath->text().isEmpty()){
        openDir = this->outputPath->text();
    }
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Load WAV file..."), openDir, tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void GainDialog::on_GainDialog_rejected()
{
    this->close();
}

