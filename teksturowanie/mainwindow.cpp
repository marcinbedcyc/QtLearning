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

void MainWindow::on_pushButton_clicked()
{
    ui->widget->resetuj();
    update();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        ui->widget->setChangePoints(true);
    }
    else{
        ui->widget->setChangePoints(false);
    }
}
