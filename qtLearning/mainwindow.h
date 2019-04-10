#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_colorButton_clicked();

    void on_clearButton_clicked();

    void on_spraySlider_valueChanged(int value);

    void on_elipseRotationSlider_valueChanged(int value);

    void on_floodFillButton_clicked();

    void on_scanLineButton_clicked();

    void on_erosionButton_clicked();

    void on_dilationButton_clicked();

    void on_openingButton_clicked();

    void on_closingButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
