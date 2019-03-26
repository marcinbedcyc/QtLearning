#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_changePointsPositionChB_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        ui->widget->setChangePoints(true);
        ui->widget->setMouseTracking(false);
    }
    else{
        ui->widget->setChangePoints(false);
        ui->widget->setMouseTracking(true);
    }
}
