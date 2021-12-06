#include "CompressionDialog.h"

#include <QFileDialog>

CompressionDialog::CompressionDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void CompressionDialog::on_pathDialogButton_clicked()
{
    auto openDir = QDir::currentPath();
    if(!this->outputPath->text().isEmpty()){
        openDir = this->outputPath->text();
    }
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Load WAV file..."), openDir, tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}

void CompressionDialog::on_CompressionDialog_rejected()
{
    this->close();
}

