#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
