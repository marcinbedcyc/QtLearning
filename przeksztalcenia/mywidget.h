#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <cmath>
#include "matrix.h"

class MyWidget : public QWidget
{
    Q_OBJECT
    QImage image;
    double **values;
    Matrix center, reverseCenter;
    std::vector<QPoint> orignalImage;
    std::vector<QPoint> resultImage;
    int red, green, blue;
    void paintEvent(QPaintEvent *);
    void putPixel(int x, int y, QImage *imag, int r, int g, int b);
    void putLineVol2(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b);
    void drawImageFromPoints();
public:
    explicit MyWidget(QWidget *parent = nullptr);
    Matrix transformation;
    void updateImage();
    ~MyWidget();

signals:

public slots:
};

#endif // MYWIDGET_H
