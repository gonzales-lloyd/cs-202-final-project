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
    /**
     * @brief Slot to open the dialog for the compression processor.
     */
    void on_openCompressionDialog_clicked();
    /**
     * @brief Slot to open the dialog for the echo processor.
     */
    void on_openEchoDialog_clicked();
    /**
     * @brief Slot to open the dialog for the low pass processor.
     */
    void on_openLowPassDialog_clicked();
    /**
     * @brief Slot to open the dialog for the gain processor.
     */
    void on_openGainDialog_clicked();
    /**
     * @brief Slot to open the dialog for the normalization processor.
     */
    void on_openNormalizationDialog_clicked();

    /**
     * @brief Slot to open filepath dialog when the path dialog button is clicked.
     */
    void on_pathDialogButton_clicked();
    /**
     * @brief Slot to call the file load functions when the Load button is clicked.
     */
    void on_loadFileButton_clicked();

    /**
     * @brief Show an informational message box with a specific text.
     * 
     * @param text The text to show in the information window. 
     */
    void showInfo(QString text);
    /**
     * @brief Show an error message box with a specific text.
     * 
     * @param text The text to show in the error window. 
     */
    void showError(QString error);

    /**
     * @brief Load the currently specified file.
     * 
     * This internally creates a new Wav object, deallocating the memory from the old one.
     */
    void loadActive();
    /**
     * @brief Save the currently specified file.
     * 
     * @param outputPath 
     */
    void saveActive(QString outputPath);

private:
    Ui::MainWindow *ui;
    Wav active_wav;

};
#endif // MAINWINDOW_H
