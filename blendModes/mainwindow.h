#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_layer0Button_clicked();

    void on_layer1Button_clicked();

    void on_layer2Button_clicked();

    void on_blendModesComboBox_currentTextChanged(const QString &arg1);

    void on_alfaSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    int currentLayerIndex;
};

#endif // MAINWINDOW_H
