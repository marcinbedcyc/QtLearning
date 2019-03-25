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
    ui->comboBox->addItems(*namesMenu);

    QPalette pal;
    pal.setColor(QPalette::Button, Qt::white);
    ui->colorButton->setAutoFillBackground(true);
    ui->colorButton->setPalette(pal);

    ui->spraySlider->setHidden(true);
    ui->elipseRotationSlider->setHidden(true);
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
    }
    else if(arg1 == "Elipsa"){
        ui->elipseRotationSlider->show();
        ui->spraySlider->setHidden(true);
    }
    else {
        ui->spraySlider->setHidden(true);
        ui->elipseRotationSlider->setHidden(true);
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
