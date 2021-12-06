#include "NormalizationDialog.h"

#include <QFileDialog>

NormalizationDialog::NormalizationDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void NormalizationDialog::on_pathDialogButton_clicked()
{
    auto openDir = QDir::currentPath();
    if(!this->outputPath->text().isEmpty()){
        openDir = this->outputPath->text();
    }
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Load WAV file..."), openDir, tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void NormalizationDialog::on_NormalizationDialog_rejected()
{
    this->close();
}

