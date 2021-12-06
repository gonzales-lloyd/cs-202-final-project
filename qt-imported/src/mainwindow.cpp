#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GainDialog.h"

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
void MainWindow::on_openGainAdjustDialog_clicked()
{
    auto gain = new GainDialog(this);
    gain->show();
}

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click
