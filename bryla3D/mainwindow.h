#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMatrix4x4>
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
    void on_xTransactionSlider_valueChanged(int value);

    void on_zRotationSlider_valueChanged(int value);

    void on_yRotationSlider_valueChanged(int value);

    void on_xRotationSlider_valueChanged(int value);

    void on_yTransactionSlider_valueChanged(int value);

    void on_zTransactionSlider_valueChanged(int value);

    void on_xScaleSlider_valueChanged(int value);

    void on_yScaleSlider_valueChanged(int value);

    void on_zScaleSlider_valueChanged(int value);

    void on_xSheeringSlider_valueChanged(int value);

    void on_ySheeringSlider_valueChanged(int value);

    void on_perspectiveCheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QMatrix4x4 rotation, scale, rotationX, rotationY, rotationZ, transaction, sheering;
    int tX, tY, tZ;
    double sX, sY, sZ;
    double shX, shY;
    void reset();
    bool isDrawing;
};

#endif // MAINWINDOW_H
