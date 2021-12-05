#include "GainDialog.h"

#include <QFileDialog>

GainDialog::GainDialog(QWidget*parent):QDialog(parent){
    setupUi(this);
}

void GainDialog::on_pathDialogButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Save output as..."), QDir::currentPath(), tr("WAV (*.wav)"));
    this->outputPath->setText(filePath);
}
