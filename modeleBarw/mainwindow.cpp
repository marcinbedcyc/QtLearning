#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileButton_clicked()
{
    QString result = QFileDialog::getOpenFileName(this,
                                                  tr("Open Image File"), "/home/marcin/Obrazy",
                                                  tr("Image File (*.jpg *png);;All Files (*)"));
    if(result != nullptr){
        ui->hSlider->setValue(0);
        ui->hSlider->setDisabled(false);
        ui->sSlider->setValue(0);
        ui->sSlider->setDisabled(false);
        ui->vSlider->setValue(0);
        ui->vSlider->setDisabled(false);
        ui->widget->setFileName(result);
    }
}

void MainWindow::on_hSlider_valueChanged(int value)
{
    ui->widget->setHPlus(value);
    ui->widget->changePixels();
}

void MainWindow::on_sSlider_valueChanged(int value)
{
    ui->widget->setSPlus(value);
    ui->widget->changePixels();
}

void MainWindow::on_vSlider_valueChanged(int value)
{
    ui->widget->setVPlus(value);
    ui->widget->changePixels();
}
