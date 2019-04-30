#include "mywidget.h"

#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage(700, 500, QImage::Format_RGB32);
    image.fill(Qt::black);
    layers[1].setImage(QImage("/home/marcin/Dokumenty/studia/Semestr IV/LGiM/blendModes/images/plaza.png"));
    layers[1].setAlfa(100);
    layers[1].setBlendMode("normal");

    layers[2].setImage(QImage("/home/marcin/Dokumenty/studia/Semestr IV/LGiM/blendModes/images/zamek.png"));
    layers[2].setAlfa(100);
    layers[2].setBlendMode("normal");

    layers[0].setImage(QImage("/home/marcin/Dokumenty/studia/Semestr IV/LGiM/blendModes/images/gradient.png"));
    layers[0].setAlfa(100);
    layers[0].setBlendMode("normal");
    mixLayers();
}

void MyWidget::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.drawImage(0, 0, image);
}

QImage MyWidget::alphaBlending(QImage *image1, QImage *image2, int alfa)
{
    int width = 700;
    int height = 500;
    int r, g, b;
    QImage result = QImage(width, height, QImage::Format_RGB32);
    QColor color, colorImage1, colorImage2;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            colorImage1 = image1->pixel(x, y);
            colorImage2 = image2->pixel(x, y);
            r = int(colorImage1.red() * (1 - alfa/100.0) + (alfa/100.0) * colorImage2.red());
            g = int(colorImage1.green() * (1 - alfa/100.0) + (alfa/100.0) * colorImage2.green());
            b = int(colorImage1.blue() * (1 - alfa/100.0) + (alfa/100.0) * colorImage2.blue());
            color.setRgb(r, g, b);
            result.setPixelColor(x, y, color);
        }
    }

    return result;
}

void MyWidget::mixLayers()
{
    int width = 700;
    int height = 500;
    QImage temp = QImage(width, height, QImage::Format_RGB32);

    image.fill(Qt::black);
    for(int i = 0; i < 3; i++){
        if(layers[i].getBlendMode() == "normal")
            temp = normalBlend(&image, &layers[i].image);
        else if(layers[i].getBlendMode() == "average")
            temp = averageBlend(&image, &layers[i].image);
        else if(layers[i].getBlendMode() == "multiply")
            temp = multiplyBlend(&image, &layers[i].image);
        else if(layers[i].getBlendMode() == "screen")
            temp = screenBlend(&image, &layers[i].image);
        else if(layers[i].getBlendMode() == "darken")
            temp = darkenBlend(&image, &layers[i].image);
        else if(layers[i].getBlendMode() == "lighten")
            temp = lightenBlend(&image, &layers[i].image);

        image = alphaBlending(&image, &temp, layers[i].getAlfa());
    }
    update();
}

Layer* MyWidget::getLayer(int index)
{
    return layers+index;
}

QImage MyWidget::normalBlend(QImage *, QImage *image2)
{
    int width = 700;
    int height = 500;
    QImage result = QImage(width, height, QImage::Format_RGB32);

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            result.setPixelColor(x, y, image2->pixel(x, y));
        }
    }

    return result;
}

QImage MyWidget::averageBlend(QImage *image1, QImage *image2)
{
    int width = 700;
    int height = 500;
    int r, g, b;
    QImage result = QImage(width, height, QImage::Format_RGB32);
    QColor color, colorImage1, colorImage2;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            colorImage1 = image1->pixel(x, y);
            colorImage2 = image2->pixel(x, y);
            r = 255 - ( (255-colorImage1.red()) * (255-colorImage2.red()) >> 8 );
            g = 255 - ( (255-colorImage1.green()) * (255-colorImage2.green()) >> 8 );
            b = 255 - ( (255-colorImage1.blue()) * (255-colorImage2.blue()) >> 8 );
            color.setRgb(r, g, b);
            result.setPixelColor(x, y, color);
        }
    }

    return result;
}

QImage MyWidget::multiplyBlend(QImage *image1, QImage *image2)
{
    int width = 700;
    int height = 500;
    int r, g, b;
    QImage result = QImage(width, height, QImage::Format_RGB32);
    QColor color, colorImage1, colorImage2;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            colorImage1 = image1->pixel(x, y);
            colorImage2 = image2->pixel(x, y);
            r = ( colorImage1.red() * colorImage2.red() ) >> 8;
            g = ( colorImage1.green() * colorImage2.green() ) >> 8;
            b = ( colorImage1.blue() * colorImage2.blue() ) >> 8;
            color.setRgb(r, g, b);
            result.setPixelColor(x, y, color);
        }
    }

    return result;
}

QImage MyWidget::screenBlend(QImage *image1, QImage *image2)
{
    int width = 700;
    int height = 500;
    int r, g, b;
    QImage result = QImage(width, height, QImage::Format_RGB32);
    QColor color, colorImage1, colorImage2;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            colorImage1 = image1->pixel(x, y);
            colorImage2 = image2->pixel(x, y);
            r = ( colorImage1.red() * colorImage2.red() ) >> 8;
            g = ( colorImage1.green() * colorImage2.green() ) >> 8;
            b = ( colorImage1.blue() * colorImage2.blue() ) >> 8;
            color.setRgb(r, g, b);
            result.setPixelColor(x, y, color);
        }
    }

    return result;
}

QImage MyWidget::darkenBlend(QImage *image1, QImage *image2)
{
    int width = 700;
    int height = 500;
    int r, g, b;
    QImage result = QImage(width, height, QImage::Format_RGB32);
    QColor color, colorImage1, colorImage2;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            colorImage1 = image1->pixel(x, y);
            colorImage2 = image2->pixel(x, y);

            if(colorImage1.red() < colorImage2.red())
                r = colorImage1.red();
            else
                r = colorImage2.red();

            if(colorImage1.green() < colorImage2.green())
                g = colorImage1.green();
            else
                g = colorImage2.green();

            if(colorImage1.blue() < colorImage2.blue())
                b = colorImage1.blue();
            else
                b = colorImage2.blue();

            color.setRgb(r, g, b);
            result.setPixelColor(x, y, color);
        }
    }

    return result;
}

QImage MyWidget::lightenBlend(QImage *image1, QImage *image2)
{
    int width = 700;
    int height = 500;
    int r, g, b;
    QImage result = QImage(width, height, QImage::Format_RGB32);
    QColor color, colorImage1, colorImage2;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            colorImage1 = image1->pixel(x, y);
            colorImage2 = image2->pixel(x, y);

            if(colorImage1.red() > colorImage2.red())
                r = colorImage1.red();
            else
                r = colorImage2.red();

            if(colorImage1.green() > colorImage2.green())
                g = colorImage1.green();
            else
                g = colorImage2.green();

            if(colorImage1.blue() > colorImage2.blue())
                b = colorImage1.blue();
            else
                b = colorImage2.blue();

            color.setRgb(r, g, b);
            result.setPixelColor(x, y, color);
        }
    }

    return result;
}
