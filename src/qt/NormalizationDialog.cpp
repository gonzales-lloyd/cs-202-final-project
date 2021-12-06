#include "NormalizationDialog.h"

#include <QFileDialog>

NormalizationDialog::NormalizationDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void NormalizationDialog::on_pathDialogButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Save output as..."), QDir::currentPath(), tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void NormalizationDialog::on_NormalizationDialog_rejected()
{
    this->close();
}

