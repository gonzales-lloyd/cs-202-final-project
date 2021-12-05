#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_gain.h"

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
    QDialog *gainDialog = new QDialog();

    Ui_GainDialog gainUi;
    gainUi.setupUi(gainDialog);

    gainDialog->show();

}

//https://stackoverflow.com/questions/13116863/qt-show-modal-dialog-ui-on-menu-item-click
