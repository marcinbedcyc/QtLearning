#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
    QImage image, orignalImage;
    QColor color;
    QString filename;
    int red, green, blue, h, s, v, hPlus, sPlus, vPlus;
    void paintEvent(QPaintEvent *);
    double minFromRGB(double &redp, double &greenp, double &bluep);
    double maxFromRGB(double &redp, double &greenp, double &bluep);

public:
    explicit MyWidget(QWidget *parent = nullptr);
    void changePixels();
    void setFileName(QString filename);
    void convertRgbToHsv();
    void convertHsvtoRgb();
    void setHPlus(int value);
    void setSPlus(int value);
    void setVPlus(int value);

signals:

public slots:
};

#endif // MYWIDGET_H
