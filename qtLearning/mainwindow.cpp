#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList *namesMenu = new QStringList();
    namesMenu->append("Linia1");
    namesMenu->append("Linia2");
    namesMenu->append("Prostokat");
    namesMenu->append("Ramka prostokata");
    namesMenu->append("Spray");
    namesMenu->append("Okrag");
    namesMenu->append("Elipsa");
    namesMenu->append("FloodFill");
    namesMenu->append("ScanLine");
    ui->comboBox->addItems(*namesMenu);

    QPalette pal;
    pal.setColor(QPalette::Button, Qt::white);
    ui->colorButton->setAutoFillBackground(true);
    ui->colorButton->setPalette(pal);

    ui->spraySlider->setHidden(true);
    ui->elipseRotationSlider->setHidden(true);
    ui->floodFillLabel->setHidden(true);
    ui->floodFillButton->setHidden(true);
    ui->scanLineButton->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->widget->setWybor(arg1);
    if(arg1 == "Spray"){
        ui->spraySlider->show();
        ui->elipseRotationSlider->setHidden(true);
        ui->floodFillLabel->setHidden(true);
        ui->floodFillButton->setHidden(true);
        ui->scanLineButton->setHidden(true);
    }
    else if(arg1 == "Elipsa"){
        ui->elipseRotationSlider->show();
        ui->spraySlider->setHidden(true);
        ui->floodFillLabel->setHidden(true);
        ui->floodFillButton->setHidden(true);
        ui->scanLineButton->setHidden(true);
    }
    else if(arg1 == "FloodFill"){
        ui->floodFillLabel->show();
        ui->floodFillButton->show();
        ui->spraySlider->setHidden(true);
        ui->elipseRotationSlider->setHidden(true);
        ui->scanLineButton->setHidden(true);
    }
    else if(arg1 == "ScanLine"){
        ui->scanLineButton->show();
        ui->floodFillLabel->setHidden(true);
        ui->floodFillButton->setHidden(true);
        ui->spraySlider->setHidden(true);
        ui->elipseRotationSlider->setHidden(true);
    }
    else {
        ui->spraySlider->setHidden(true);
        ui->elipseRotationSlider->setHidden(true);
        ui->floodFillLabel->setHidden(true);
        ui->floodFillButton->setHidden(true);
        ui->scanLineButton->setHidden(true);
    }
}

void MainWindow::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);
    color.getRgb(&ui->widget->red, &ui->widget->green, &ui->widget->blue);

    QPalette pal;
    pal.setColor(QPalette::Button, color);
    ui->colorButton->setAutoFillBackground(true);
    ui->colorButton->setPalette(pal);
}

void MainWindow::on_clearButton_clicked()
{
    ui->widget->clearIm();
    ui->widget->update();
    ui->widget->scanLinePoints.clear();
    ui->widget->setIsPaintedElipse(false);
}

void MainWindow::on_spraySlider_valueChanged(int value)
{
    ui->widget->setSpraySize(value);
}

void MainWindow::on_elipseRotationSlider_valueChanged(int value)
{
    if(ui->widget->getIsPaintedElipse()){
        ui->widget->setElipseBeta(value/100.0);
        ui->widget->paintRotatedElipse();
    }
}

void MainWindow::on_floodFillButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this);
    ui->widget->fillColor = color;

    QPalette pal;
    pal.setColor(QPalette::Button, color);
    ui->floodFillButton->setAutoFillBackground(true);
    ui->floodFillButton->setPalette(pal);
}

void MainWindow::on_scanLineButton_clicked()
{
    ui->widget->scanLine(ui->widget->scanLinePoints);
    update();
}
