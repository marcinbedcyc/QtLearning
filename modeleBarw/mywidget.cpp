#include "mywidget.h"

#include <QPainter>
#include <cmath>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(1000, 400, QImage::Format_RGB32);
    orignalImage = QImage(1000, 400, QImage::Format_RGB32);
    hPlus = sPlus = vPlus = 0;
}

void MyWidget::changePixels()
{
    QColor color;
    for(int y=0; y < image.size().height(); y++){
        for(int x = 0; x < image.size().width(); x++){
            orignalImage.pixelColor(x, y).getRgb(&red, &green, &blue);
            convertRgbToHsv();
            if(hPlus <= 0 )
                hPlus += 360;

            h += hPlus;     
            s += sPlus;
            v += vPlus;

            h = h % 360;

            if(s >=255 )s = 255;
            else if(s <= 0) s = 0;

            if(v >=255 )v = 255;
            else if(v <= 0) v = 0;

            convertHsvtoRgb();
            color.setRgb(red, green, blue);
            image.setPixelColor(x, y, color);
        }
    }
    update();
}

void MyWidget::setFileName(QString filename)
{
    this->filename = filename;
    image.load(filename);
    orignalImage.load(filename);
    update();
}


void MyWidget::convertRgbToHsv()
{
    double redPrim, greenPrim, bluePrim;
    double cMax, cMin, delta;

    redPrim = red/255.0;
    greenPrim = green/255.0;
    bluePrim = blue/255.0;

    cMin = minFromRGB(redPrim, greenPrim, bluePrim);
    cMax = maxFromRGB(redPrim, greenPrim, bluePrim);
    delta = cMax - cMin;

    v = int(cMax*255.0);

    if(cMax == 0)
        s = 0;
    else
        s = int((delta/cMax)*255.0);

   if(delta == 0)
       h = 0;
   else if(cMax == redPrim)
       h = int(60 * ((int((greenPrim - bluePrim)/delta))%6));
   else if(cMax == greenPrim)
       h = int(60 * ( ( (bluePrim - redPrim)/delta ) + 2));
   else /*if(cMax == bluePrim)*/
       h = int(60 * ( ( (redPrim-greenPrim)/delta ) + 4));
}

void MyWidget::convertHsvtoRgb()
{
    int hInside;
    double sInside, vInside, c, x, m;
    double redPrim, greenPrim, bluePrim;

    hInside = h;
    sInside = s/255.0;
    vInside = v/255.0;

    c = vInside * sInside;
    x = c * ( 1 - abs((h/60)%2 -1) );
    m = vInside - c;

    if( h >= 0 && h < 60){
        redPrim = c;
        greenPrim = x;
        bluePrim = 0;
    }
    else if ( h >= 60 && h < 120) {
        redPrim = x;
        greenPrim = c;
        bluePrim = 0;
    }
    else if (h >= 120 && h < 180) {
        redPrim = 0;
        greenPrim = c;
        bluePrim = x;
    }
    else if (h >= 180 && h < 240) {
        redPrim = 0;
        greenPrim = x;
        bluePrim = c;
    }
    else if (h >= 240 && h < 300) {
        redPrim = x;
        greenPrim = 0;
        bluePrim = c;
    }
    else /*if (h >=300 && h < 360)*/ {
        redPrim = c;
        greenPrim = 0;
        bluePrim = x;
    }

    red = int((redPrim+m)*255);
    green = int((greenPrim+m)*255);
    blue = int((bluePrim+m)*255);

}

void MyWidget::setHPlus(int value)
{
    hPlus = value;
}

void MyWidget::setSPlus(int value)
{
    sPlus = value;
}

void MyWidget::setVPlus(int value)
{
    vPlus = value;
}

void MyWidget::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.drawImage(0, 0, image);
}

double MyWidget::minFromRGB(double &redp, double &greenp, double &bluep)
{
    if(redp < greenp){
        if(redp < bluep)
            return redp;
        else
            return bluep;
    }
    else{
        if(greenp < bluep)
            return greenp;
        else {
            return bluep;
        }
    }
}

double MyWidget::maxFromRGB(double &redp, double &greenp, double &bluep)
{
    if(redp > greenp){
        if(redp > bluep)
            return redp;
        else
            return bluep;
    }
    else{
        if(greenp > bluep)
            return greenp;
        else {
            return bluep;
        }
    }
}
