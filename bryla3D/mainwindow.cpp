#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reset();
    isDrawing = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_xTransactionSlider_valueChanged(int value)
{
    tX = value/3;
    transaction = QMatrix4x4(1, 0, 0, tX,
                             0, 1, 0, tY,
                             0, 0, 1, tZ,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
}

void MainWindow::on_zRotationSlider_valueChanged(int value)
{
    if(isDrawing){
    double alfa = value * M_PI / 180.0;
    rotationZ = QMatrix4x4(float(cos(alfa)), float(-1 * sin(alfa)), 0, 0,
                          float(sin(alfa)), float(cos(alfa)), 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_yRotationSlider_valueChanged(int value)
{
    if(isDrawing){
    double alfa = value * M_PI / 180.0;
    rotationY = QMatrix4x4(float(cos(alfa)), 0, float(sin(alfa)), 0,
                          0, 1, 0, 0,
                          float(-1 * sin(alfa)), 0, float(cos(alfa)), 0,
                          0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_xRotationSlider_valueChanged(int value)
{
    if(isDrawing){
    double alfa = value * M_PI / 180.0;
    rotationX = QMatrix4x4(1, 0, 0, 0,
                          0, float(cos(alfa)), float(-1 * sin(alfa)), 0,
                          0, float(sin(alfa)), float(cos(alfa)), 0,
                          0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_yTransactionSlider_valueChanged(int value)
{
    if(isDrawing){
    tY = value/3;
    transaction = QMatrix4x4(1, 0, 0, tX,
                             0, 1, 0, tY,
                             0, 0, 1, tZ,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_zTransactionSlider_valueChanged(int value)
{
    if(isDrawing){
    tZ = value/3;
    transaction = QMatrix4x4(1, 0, 0, tX,
                             0, 1, 0, tY,
                             0, 0, 1, tZ,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_xScaleSlider_valueChanged(int value)
{
    if(isDrawing){
    if(ui->isScalablyHomogeneous->isChecked()){
        ui->yScaleSlider->setValue(value);
        ui->zScaleSlider->setValue(value);
    }
    sX = value/100.0;
    scale = QMatrix4x4(float(sX), 0, 0, 0,
                             0, float(sY), 0, 0,
                             0, 0, float(sZ), 0,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_yScaleSlider_valueChanged(int value)
{
    if(isDrawing){
    if(ui->isScalablyHomogeneous->isChecked()){
        ui->xScaleSlider->setValue(value);
        ui->zScaleSlider->setValue(value);
    }
    sY = value/100.0;
    scale = QMatrix4x4(float(sX), 0, 0, 0,
                             0, float(sY), 0, 0,
                             0, 0, float(sZ), 0,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_zScaleSlider_valueChanged(int value)
{
    if(isDrawing){
    if(ui->isScalablyHomogeneous->isChecked()){
        ui->yScaleSlider->setValue(value);
        ui->xScaleSlider->setValue(value);
    }
    sZ = value/100.0;
    scale = QMatrix4x4(float(sX), 0, 0, 0,
                             0, float(sY), 0, 0,
                             0, 0, float(sZ), 0,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_xSheeringSlider_valueChanged(int value)
{
    if(isDrawing){
    shX = value/100.0;
    sheering = QMatrix4x4(1, 0, float(shX), 0,
                             0, 1, float(shY), 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_ySheeringSlider_valueChanged(int value)
{
    if(isDrawing){
    shY = value/100.0;
    sheering = QMatrix4x4(1, 0, float(shX), 0,
                             0, 1, float(shY), 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
    rotation = (rotationX * rotationY * rotationZ);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
    ui->widget->drawPicture();
    }
}

void MainWindow::on_perspectiveCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        ui->widget->setIsPerspective(true);
        reset();
        ui->widget->drawPicture();
    }
    else{
        ui->widget->setIsPerspective(false);
        reset();
        ui->widget->drawPicture();
    }
}

void MainWindow::reset()
{
    transaction = QMatrix4x4(1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);

    scale = QMatrix4x4(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);

    rotationX = QMatrix4x4(1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1);


    rotationY = QMatrix4x4(1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1);


    rotationZ = QMatrix4x4(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);

    sheering = QMatrix4x4(1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);


    rotation = (rotationX * rotationY * rotationZ);

    tX = tY = tZ = 0;
    sX = sY = sZ = 1;
    shX = shY = 0;

    isDrawing = false;
    ui->xScaleSlider->setValue(100);
    ui->yScaleSlider->setValue(100);
    ui->zScaleSlider->setValue(100);
    ui->xRotationSlider->setValue(0);
    ui->yRotationSlider->setValue(0);
    ui->zRotationSlider->setValue(0);
    ui->xTransactionSlider->setValue(0);
    ui->yTransactionSlider->setValue(0);
    ui->zTransactionSlider->setValue(0);
    ui->xSheeringSlider->setValue(0);
    ui->ySheeringSlider->setValue(0);
    isDrawing = true;

    ui->zTransactionSlider->setValue(15);
    ui->widget->transformation = (transaction * scale * rotation * sheering);
}
