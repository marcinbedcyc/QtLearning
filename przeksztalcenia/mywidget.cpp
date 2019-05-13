#include "mywidget.h"

#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent){
    image = QImage(800, 500, QImage::Format_RGB32);
    image.fill(Qt::black);
    red = green = blue = 255;
    orignalImage.push_back(QPoint(200,150));
    orignalImage.push_back(QPoint(400,50));
    orignalImage.push_back(QPoint(600,150));
    orignalImage.push_back(QPoint(600,400));
    orignalImage.push_back(QPoint(200,400));

    values = new double*[3];
    for(int i=0 ; i< 3; i++){
        values[i] = new double[3];
    }

    double alfa = 100.00 * M_PI / 180.0;
    double sh = 0.1;

    values[0][0] = 1;//cos(alfa);
    values[0][1] = 0;///-1 * sin(alfa);
    values[0][2] = 0;
    values[1][0] = 0;//sin(alfa);
    values[1][1] = 1;//cos(alfa);
    values[1][2] = 0;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;

    transformation = values;

    values[0][0] = 1;
    values[0][1] = 0;
    values[0][2] = 400;
    values[1][0] = 0;
    values[1][1] = 1;
    values[1][2] = 250;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;

    center = values;

    values[0][0] = 1;
    values[0][1] = 0;
    values[0][2] = -400;
    values[1][0] = 0;
    values[1][1] = 1;
    values[1][2] = -250;
    values[2][0] = 0;
    values[2][1] = 0;
    values[2][2] = 1;

    reverseCenter = values;
    updateImage();
}

void MyWidget::updateImage(){
    transformation = center * transformation * reverseCenter;
    image.fill(Qt::black);
    resultImage.clear();
    unsigned long size = orignalImage.size();
    for(unsigned long i=0; i < size; i++){
        resultImage.push_back(transformation * orignalImage[i]);
    }
    drawImageFromPoints();
    update();
}

MyWidget::~MyWidget(){
    for(int i = 0; i < 3; i++)
       delete [] values[i];
    delete [] values;
}

void MyWidget::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.drawImage(0, 0, image);
}

void MyWidget::drawImageFromPoints(){
    unsigned long size = resultImage.size();
    putLineVol2(resultImage[size-1].x(), resultImage[size-1].y(), resultImage[0].x(), resultImage[0].y(), &image, red, green, blue);
    for(unsigned long i=1; i < size; i++){
        putLineVol2(resultImage[i-1].x(), resultImage[i-1].y(), resultImage[i].x(), resultImage[i].y(), &image, red, green, blue);
    }

}

void MyWidget::putPixel(int x, int y, QImage *imag, int r, int g, int b){
    if( y >= 0 && x >= 0 && x < imag->width() && y < imag->height()){
        uchar *p = imag->scanLine(y);
        p[x*4] = uchar(b);
        p[x*4 + 1] = uchar(g);
        p[x*4 + 2] = uchar(r);
    }
}

void MyWidget::putLineVol2(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b){
    int y, x, dy, dx;
    float t;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    if(dx >= dy && x1 < x2){
        for(int x = x1; x <= x2; x++){
            t = float(x - x1) / (x2 - x1);
            y = int(y1 + t * (y2 - y1));
            putPixel(x, y, imag, r, g, b);
        }
    }
    else if(dx >= dy && x2 < x1){
        for(int x = x2; x <= x1; x++){
            t = float(x - x2) / (x1 - x2);
            y = int(y2 + t * (y1 - y2));
            putPixel(x, y, imag, r, g, b);
        }
    }
    else if(dy > dx && y1 < y2){
        for(int y = y1; y <= y2; y++){
            t = float(y - y1) / (y2 - y1);
            x = int(x1 + t * (x2 - x1));
            putPixel(x, y, imag, r, g, b);

        }
    }
    else if(dy > dx && y1 > y2){
        for(int y = y2; y <= y1; y++){
            t = float(y - y2) / (y1 - y2);
            x = int(x2 + t * (x1 - x2));
            putPixel(x, y, imag, r, g, b);
        }
    }
}

