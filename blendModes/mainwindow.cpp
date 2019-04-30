#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->blendModesComboBox->addItem("normal");
    ui->blendModesComboBox->addItem("average");
    ui->blendModesComboBox->addItem("multiply");
    ui->blendModesComboBox->addItem("screen");
    ui->blendModesComboBox->addItem("darken");
    ui->blendModesComboBox->addItem("lighten");

    ui->layer2Button->setChecked(true);
    ui->blendModesComboBox->setCurrentText(ui->widget->getLayer(2)->getBlendMode());
    ui->alfaSlider->setValue(ui->widget->getLayer(2)->getAlfa());
    currentLayerIndex = 2;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_layer0Button_clicked()
{
    currentLayerIndex = 0;
    ui->blendModesComboBox->setCurrentText(ui->widget->getLayer(0)->getBlendMode());
    ui->alfaSlider->setValue(ui->widget->getLayer(0)->getAlfa());
}

void MainWindow::on_layer1Button_clicked()
{
    currentLayerIndex = 1;
    ui->blendModesComboBox->setCurrentText(ui->widget->getLayer(1)->getBlendMode());
    ui->alfaSlider->setValue(ui->widget->getLayer(1)->getAlfa());
}

void MainWindow::on_layer2Button_clicked()
{
    currentLayerIndex = 2;
    ui->blendModesComboBox->setCurrentText(ui->widget->getLayer(2)->getBlendMode());
    ui->alfaSlider->setValue(ui->widget->getLayer(2)->getAlfa());
}

void MainWindow::on_blendModesComboBox_currentTextChanged(const QString &arg1)
{
    ui->widget->getLayer(currentLayerIndex)->setBlendMode(arg1);
    ui->widget->mixLayers();
}


void MainWindow::on_alfaSlider_valueChanged(int value)
{
    ui->widget->getLayer(currentLayerIndex)->setAlfa(value);
    ui->widget->mixLayers();
}
