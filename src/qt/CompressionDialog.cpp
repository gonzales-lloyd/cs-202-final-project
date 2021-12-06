#include "CompressionDialog.h"

#include <QFileDialog>

CompressionDialog::CompressionDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void CompressionDialog::on_pathDialogButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Save output as..."), QDir::currentPath(), tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void CompressionDialog::on_CompressionDialog_rejected()
{
    this->close();
}

