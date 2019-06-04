#include "mywidget.h"

#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(800, 680, QImage::Format_RGB32);
    image.fill(Qt::black);
    red = green = blue = 255;
    isPerspective = false;

    /*orginalImage.push_back(QVector3D(-100,100,100));
    orginalImage.push_back(QVector3D(100,100,100));
    orginalImage.push_back(QVector3D(100,-100,100));
    orginalImage.push_back(QVector3D(-100,-100,100));
    orginalImage.push_back(QVector3D(-100,100,-100));
    orginalImage.push_back(QVector3D(100,100,-100));
    orginalImage.push_back(QVector3D(100,-100,-100));
    orginalImage.push_back(QVector3D(-100,-100,-100));*/

    orginalImage.push_back(QVector3D(-1,1,-1));
    orginalImage.push_back(QVector3D(1,1,-1));
    orginalImage.push_back(QVector3D(1,-1,-1));
    orginalImage.push_back(QVector3D(-1,-1,-1));
    orginalImage.push_back(QVector3D(-1,1,1));
    orginalImage.push_back(QVector3D(1,1,1));
    orginalImage.push_back(QVector3D(1,-1,1));
    orginalImage.push_back(QVector3D(-1,-1,1));

    transformation = QMatrix4x4(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);

    center = QMatrix4x4(1, 0, 0, 400,
                        0, 1, 0, 340,
                        0, 0, 1, 0,
                        0, 0, 0, 1);


    reverseCenter = QMatrix4x4(1, 0, 0, -400,
                               0, 1, 0, -340,
                               0, 0, 1, 0,
                               0, 0, 0, 1);

    drawPicture();
}

void MyWidget::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.drawImage(0, 0, image);
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

void MyWidget::rzutRownolegly()
{
    imageToDraw.clear();
    for(int i = 0; i < resultImage.size(); i++){
        imageToDraw.push_back(resultImage[i].toPoint());
    }
}

void MyWidget::rzutPerspektywiczny()
{
    imageToDraw.clear();
    int cX = 400;
    int cY = 340;
    int f = 300;
    float x, y, z;
    for(int i=0; i < resultImage.size(); i ++){
        x = resultImage[i].x();
        y = resultImage[i].y();
        z = resultImage[i].z();
        if(double(z) < 0.1){
            x = -1;
            y = -1;
        }
        else{
            x = x * f / z + cX;
            y = y * f / z  + cY;
        }
        imageToDraw.push_back(QPoint(int(x), int(y)));
    }
}

bool MyWidget::getIsPerspective() const
{
    return isPerspective;
}

void MyWidget::setIsPerspective(bool value)
{
    isPerspective = value;
}

void MyWidget::drawPicture()
{
    orginalImage.clear();
    if(!isPerspective){
        transformation = center * transformation;
        orginalImage.push_back(QVector3D(-100,100,100));
        orginalImage.push_back(QVector3D(100,100,100));
        orginalImage.push_back(QVector3D(100,-100,100));
        orginalImage.push_back(QVector3D(-100,-100,100));
        orginalImage.push_back(QVector3D(-100,100,-100));
        orginalImage.push_back(QVector3D(100,100,-100));
        orginalImage.push_back(QVector3D(100,-100,-100));
        orginalImage.push_back(QVector3D(-100,-100,-100));
    }
    else {
        orginalImage.push_back(QVector3D(-1,1,-1));
        orginalImage.push_back(QVector3D(1,1,-1));
        orginalImage.push_back(QVector3D(1,-1,-1));
        orginalImage.push_back(QVector3D(-1,-1,-1));
        orginalImage.push_back(QVector3D(-1,1,1));
        orginalImage.push_back(QVector3D(1,1,1));
        orginalImage.push_back(QVector3D(1,-1,1));
        orginalImage.push_back(QVector3D(-1,-1,1));
    }
    
    image.fill(Qt::black);
    
    resultImage.clear();
    for(int i=0;i< orginalImage.size(); i++){
        resultImage.push_back(transformation.map(orginalImage[i]));
    }

    if(isPerspective)
        rzutPerspektywiczny();
    else
        rzutRownolegly();
    if(!(imageToDraw[0].x() == -1 || imageToDraw[0].y() == -1 || imageToDraw[1].x() == -1 || imageToDraw[1].y() == -1))
        putLineVol2(imageToDraw[0].x(), imageToDraw[0].y(), imageToDraw[1].x(), imageToDraw[1].y(), &image, red, green, blue);
    if(!(imageToDraw[1].x() == -1 || imageToDraw[1].y() == -1 || imageToDraw[2].x() == -1 || imageToDraw[2].y() == -1))
        putLineVol2(imageToDraw[1].x(), imageToDraw[1].y(), imageToDraw[2].x(), imageToDraw[2].y(), &image, red, green, blue);
    if(!(imageToDraw[2].x() == -1 || imageToDraw[2].y() == -1 || imageToDraw[3].x() == -1 || imageToDraw[3].y() == -1))
        putLineVol2(imageToDraw[2].x(), imageToDraw[2].y(), imageToDraw[3].x(), imageToDraw[3].y(), &image, red, green, blue);
    if(!(imageToDraw[3].x() == -1 || imageToDraw[3].y() == -1 || imageToDraw[0].x() == -1 || imageToDraw[0].y() == -1))
        putLineVol2(imageToDraw[3].x(), imageToDraw[3].y(), imageToDraw[0].x(), imageToDraw[0].y(), &image, red, green, blue);

    if(!(imageToDraw[4].x() == -1 || imageToDraw[4].y() == -1 || imageToDraw[5].x() == -1 || imageToDraw[5].y() == -1))
        putLineVol2(imageToDraw[4].x(), imageToDraw[4].y(), imageToDraw[5].x(), imageToDraw[5].y(), &image, red, green, blue);
    if(!(imageToDraw[5].x() == -1 || imageToDraw[5].y() == -1 || imageToDraw[6].x() == -1 || imageToDraw[6].y() == -1))
        putLineVol2(imageToDraw[5].x(), imageToDraw[5].y(), imageToDraw[6].x(), imageToDraw[6].y(), &image, red, green, blue);
    if(!(imageToDraw[6].x() == -1 || imageToDraw[6].y() == -1 || imageToDraw[7].x() == -1 || imageToDraw[7].y() == -1))
        putLineVol2(imageToDraw[6].x(), imageToDraw[6].y(), imageToDraw[7].x(), imageToDraw[7].y(), &image, red, green, blue);
    if(!(imageToDraw[7].x() == -1 || imageToDraw[7].y() == -1 || imageToDraw[4].x() == -1 || imageToDraw[4].y() == -1))
        putLineVol2(imageToDraw[7].x(), imageToDraw[7].y(), imageToDraw[4].x(), imageToDraw[4].y(), &image, red, green, blue);

    if(!(imageToDraw[0].x() == -1 || imageToDraw[0].y() == -1 || imageToDraw[4].x() == -1 || imageToDraw[4].y() == -1))
        putLineVol2(imageToDraw[0].x(), imageToDraw[0].y(), imageToDraw[4].x(), imageToDraw[4].y(), &image, red, green, blue);
    if(!(imageToDraw[0].x() == -1 || imageToDraw[0].y() == -1 || imageToDraw[5].x() == -1 || imageToDraw[5].y() == -1))
        putLineVol2(imageToDraw[1].x(), imageToDraw[1].y(), imageToDraw[5].x(), imageToDraw[5].y(), &image, red, green, blue);
    if(!(imageToDraw[0].x() == -1 || imageToDraw[0].y() == -1 || imageToDraw[6].x() == -1 || imageToDraw[6].y() == -1))
        putLineVol2(imageToDraw[2].x(), imageToDraw[2].y(), imageToDraw[6].x(), imageToDraw[6].y(), &image, red, green, blue);
    if(!(imageToDraw[0].x() == -1 || imageToDraw[0].y() == -1 || imageToDraw[7].x() == -1 || imageToDraw[7].y() == -1))
        putLineVol2(imageToDraw[3].x(), imageToDraw[3].y(), imageToDraw[7].x(), imageToDraw[7].y(), &image, red, green, blue);

    update();
}
