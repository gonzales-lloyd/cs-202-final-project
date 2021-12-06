#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GainDialog.h"
#include "CompressionDialog.h"
#include "EchoDialog.h"
#include "NormalizationDialog.h"
#include "LowPassDialog.h"

#include <QtWidgets/QDialog>

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
void MainWindow::on_openEchoDialog_clicked()
{
    auto echo = new EchoDialog(this);
    echo->show();
}

void MainWindow::on_openGainDialog_clicked()
{
    auto gain = new GainDialog(this);
    gain->show();
}

void MainWindow::on_openNormalizationDialog_clicked()
{
    auto normalization = new NormalizationDialog(this);
    normalization->show();
}

void MainWindow::on_openLowPassDialog_clicked()
{
    auto lowpass = new LowPassDialog(this);
    lowpass->show();
}

void MainWindow::on_openCompressionDialog_clicked()
{
    auto compression = new CompressionDialog(this);
    compression->show();
}

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click


