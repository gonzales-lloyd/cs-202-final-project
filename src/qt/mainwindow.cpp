#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//https://stackoverflow.com/questions/10017025/qt-creator-error-message
void MainWindow::showError(QString error){
    QMessageBox messageBox;
    messageBox.critical(0, "Error", error);
    messageBox.setFixedSize(500,200);
}

void MainWindow::showInfo(QString text){
    QMessageBox messageBox;
    messageBox.information(0, "Info", text);
    messageBox.setFixedSize(500,200);
}

void MainWindow::on_openEchoDialog_clicked()
{
    if(!active_wav.fileLoaded){
        showError("You need to load a file first!");
        return;
    }
    auto echo = new EchoDialog(this);
    if(echo->exec() == QDialog::Accepted){
        double selectionStart = echo->selectionStart->value();
        double selectionEnd = echo->selectionEnd->value();
        double decayFactor = echo->decayFactor->value();
        double echoDelay = echo->echoDelay->value();
        QString outputPath = echo->outputPath->text();
        if(outputPath.isEmpty()){
            showError("Please specify a save location!");
            return;
        }
        WavManipulation::echo(active_wav, selectionStart, selectionEnd, decayFactor, echoDelay);
        saveActive(outputPath);
    }
}

void MainWindow::on_openGainDialog_clicked()
{
    if(!active_wav.fileLoaded){
        showError("You need to load a file first!");
        return;
    }
    auto gain = new GainDialog(this);
    if(gain->exec() == QDialog::Accepted){
        double scaleFactor = gain->scaleFactor->value();
        QString outputPath = gain->outputPath->text();
        if(outputPath.isEmpty()){
            showError("Please specify a save location!");
            return;
        }
        WavManipulation::adjust_gain(active_wav, scaleFactor);
        saveActive(outputPath);
    }
}

void MainWindow::on_openNormalizationDialog_clicked()
{
    if(!active_wav.fileLoaded){
        showError("You need to load a file first!");
        return;
    }
    auto normalization = new NormalizationDialog(this);
    if(normalization->exec() == QDialog::Accepted){
        QString outputPath = normalization->outputPath->text();
        if(outputPath.isEmpty()){
            showError("Please specify a save location!");
            return;
        }
        WavManipulation::normalize(active_wav);
        saveActive(outputPath);
    }
}

void MainWindow::on_openLowPassDialog_clicked()
{
    if(!active_wav.fileLoaded){
        showError("You need to load a file first!");
        return;
    }
    auto lowpass = new LowPassDialog(this);
    if(lowpass->exec() == QDialog::Accepted){
        int sampleDelay = lowpass->sampleDelay->value();
        double scaleFactor = lowpass->scaleFactor->value();
        QString outputPath = lowpass->outputPath->text();
        if(outputPath.isEmpty()){
            showError("Please specify a save location!");
            return;
        }
        WavManipulation::lowpass(active_wav, sampleDelay, scaleFactor);
        saveActive(outputPath);
    }
}

void MainWindow::on_openCompressionDialog_clicked()
{
    if(!active_wav.fileLoaded){
        showError("You need to load a file first!");
        return;
    }
    auto compression = new CompressionDialog(this);
    if(compression->exec() == QDialog::Accepted){
        double threshold = compression->threshold->value();
        double attenuation = compression->attenuationFactor->value();
        QString outputPath = compression->outputPath->text();
        if(outputPath.isEmpty()){
            showError("Please specify a save location!");
            return;
        }
        WavManipulation::compress(active_wav, threshold, attenuation);
        saveActive(outputPath);
    }
}

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click

void MainWindow::on_pathDialogButton_clicked()
{
    QString openDir = QDir::currentPath();
    if(!ui->inputPath->text().isEmpty()){
        openDir = ui->inputPath->text();
    }
    QString filePath = QFileDialog::getOpenFileName(this,
         tr("Load WAV file..."), openDir, tr("WAV (*.wav)"));
    if(!filePath.isEmpty()){
         ui->inputPath->setText(filePath);
    }
}

void MainWindow::loadActive(){
    QString filePath = ui->inputPath->text();
    if(filePath.isEmpty()){
        showError("You must specify a file path first!");
        return;
    }
    try{
        active_wav.readFile(filePath.toStdString());
        ui->metadataText->document()->setPlainText(QString::fromStdString(active_wav.getMetaData()));
    }catch(const std::runtime_error &e){
        showError(e.what());
    }
}

void MainWindow::saveActive(QString outputPath){
    try{
        active_wav.writeFile(outputPath.toStdString());
        showInfo("File saved!");
        loadActive();
    }catch(std::runtime_error &e){
        showError(e.what());
    }
}

void MainWindow::on_loadFileButton_clicked()
{
    loadActive();
}

