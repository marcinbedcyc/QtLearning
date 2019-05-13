#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matrix.h"

#include <QMainWindow>
#include <cmath>

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
    void on_rotationSlider_valueChanged(int value);

    void on_transactionSliderX_valueChanged(int value);

    void on_transactionSliderY_valueChanged(int value);

    void on_scaleSliderX_valueChanged(int value);

    void on_scaleSliderY_valueChanged(int value);

    void on_shearingSliderX_valueChanged(int value);

    void on_shearingSliderY_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    double **values;
    Matrix rotation, scale, transaction, shearing;
    int tX, tY;
    double sX, sY;
    double shX, shY;
};

#endif // MAINWINDOW_H
