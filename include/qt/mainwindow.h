#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_mainwindow.h"

#include "GainDialog.h"
#include "CompressionDialog.h"
#include "EchoDialog.h"
#include "NormalizationDialog.h"
#include "LowPassDialog.h"

#include <QtWidgets/QDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "wav.h"
#include "wavmanip.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openCompressionDialog_clicked();
    void on_openEchoDialog_clicked();
    void on_openLowPassDialog_clicked();
    void on_openGainDialog_clicked();
    void on_openNormalizationDialog_clicked();

    void on_pathDialogButton_clicked();

    void on_loadFileButton_clicked();

    void showInfo(QString error);
    void showError(QString error);

    void loadActive();
    void saveActive(QString outputPath);

private:
    Ui::MainWindow *ui;
    Wav active_wav;

};
#endif // MAINWINDOW_H
