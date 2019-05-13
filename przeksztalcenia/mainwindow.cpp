#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    values = new double*[3];
    for(int i=0 ; i< 3; i++){
        values[i] = new double[3];
    }

    values[0][0] = 1;
    values[0][1] = 0;
    values[0][2] = 0;
    values[1][0] = 0;
    values[1][1] = 1;
    values[1][2] = 0;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;

    transaction = rotation = scale = shearing = values;
    tX = tY = 0;
    sX = sY = 1;
    shX = shY = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    for(int i = 0; i < 3; i++)
       delete [] values[i];
    delete [] values;
}

void MainWindow::on_rotationSlider_valueChanged(int value)
{
    double alfa = value * M_PI / 180.0;
    values[0][0] = cos(alfa);
    values[0][1] = -1 * sin(alfa);
    values[0][2] = 0;
    values[1][0] = sin(alfa);
    values[1][1] = cos(alfa);
    values[1][2] = 0;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;
    rotation = values;
    ui->widget->transformation = transaction * scale * rotation * shearing;
    ui->widget->updateImage();
}

void MainWindow::on_transactionSliderX_valueChanged(int value)
{
    tX = value;
    values[0][0] = 1;
    values[0][1] = 0;
    values[0][2] = tX;
    values[1][0] = 0;
    values[1][1] = 1;
    values[1][2] = tY;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;
    transaction = values;
    ui->widget->transformation = transaction * scale * rotation * shearing;
    ui->widget->updateImage();
}

void MainWindow::on_transactionSliderY_valueChanged(int value)
{
    tY = value;
    values[0][0] = 1;
    values[0][1] = 0;
    values[0][2] = tX;
    values[1][0] = 0;
    values[1][1] = 1;
    values[1][2] = tY;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;
    transaction = values;
    ui->widget->transformation = transaction * scale * rotation * shearing;
    ui->widget->updateImage();
}

void MainWindow::on_scaleSliderX_valueChanged(int value)
{
    if(ui->isScalablyHomogeneous->isChecked())
        ui->scaleSliderY->setValue(value);

    sX = value/100.0;
    values[0][0] = sX;
    values[0][1] = 0;
    values[0][2] = 0;
    values[1][0] = 0;
    values[1][1] = sY;
    values[1][2] = 0;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;
    scale = values;
    ui->widget->transformation = transaction * scale * rotation * shearing;
    ui->widget->updateImage();
}

void MainWindow::on_scaleSliderY_valueChanged(int value)
{
    if(ui->isScalablyHomogeneous->isChecked())
        ui->scaleSliderX->setValue(value);

    sY = value/100.0;
    values[0][0] = sX;
    values[0][1] = 0;
    values[0][2] = 0;
    values[1][0] = 0;
    values[1][1] = sY;
    values[1][2] = 0;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;
    scale = values;
    ui->widget->transformation = transaction * scale * rotation * shearing;
    ui->widget->updateImage();
}

void MainWindow::on_shearingSliderX_valueChanged(int value)
{
    shX = value/100.0;
    values[0][0] = 1;
    values[0][1] = shX;
    values[0][2] = 0;
    values[1][0] = shY;
    values[1][1] = 1;
    values[1][2] = 0;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;
    shearing = values;
    ui->widget->transformation = transaction * scale * rotation * shearing;
    ui->widget->updateImage();
}

void MainWindow::on_shearingSliderY_valueChanged(int value)
{
    shY = value/100.0;
    values[0][0] = 1;
    values[0][1] = shX;
    values[0][2] = 0;
    values[1][0] = shY;
    values[1][1] = 1;
    values[1][2] = 0;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;
    shearing = values;
    ui->widget->transformation = transaction * scale * rotation * shearing;
    ui->widget->updateImage();
}
