#include "mywidget.h"

#include <QDebug>
#include <QPainter>
#include <cmath>
#include <algorithm>
#include <stack>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    im  = QImage(900, 600, QImage::Format_RGB32);
    red = green = blue = 255;
    copy = im;
    spraySize = 30;
    elipseBeta = 0;
    isPaintedElipse = false;

    std::vector<QPoint> punkty;
    punkty.push_back(QPoint(300, 50));
    //putPixel(300, 50, &im, 255, 255, 255);

    punkty.push_back(QPoint(400, 150));
    //putPixel(400, 150, &im, 255, 255, 255);

    punkty.push_back(QPoint(500, 50));
    //putPixel(500, 50, &im, 255, 255, 255);

    punkty.push_back(QPoint(400, 200));
    //putPixel(300, 200, &im, 255, 255, 255);

    punkty.push_back(QPoint(300, 250));
    //putPixel(300, 250, &im, 255, 255, 255);

    punkty.push_back(QPoint(200, 150));
    //putPixel(200, 150, &im, 255, 255, 255);

    //scanLine(punkty);
}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(0, 0, this->width(), this->height(), Qt::green);
    p.drawImage(0, 0, im);
}


void MyWidget::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();

    //rysowanie prostokąta prostokata w każdym kierunku
    if(wybor == "Prostokat"){
        //im.fill(Qt::black);
        im = copy;
        if(pressX > x && pressY > y)
            putRect(x, y, pressX - x, pressY - y,&im, red, green, blue);
        else if(pressX > x)
            putRect(x, pressY, pressX - x, y - pressY ,&im , red, green, blue);
        else if(pressY > y)
            putRect(pressX, y, x - pressX, pressY - y ,&im , red, green, blue);
        else
            putRect(pressX, pressY, x - pressX, y - pressY,&im, red, green, blue);
    }

    //rysowanie ramek prostokata w każdym kierunku
    else if(wybor == "Ramka prostokata"){
        //im.fill(Qt::black);
        im = copy;
        if(pressX > x && pressY > y)
            putRectFrame(x, y, pressX - x, pressY - y,&im, red, green, blue);
        else if(pressX > x)
            putRectFrame(x, pressY, pressX - x, y - pressY ,&im , red, green, blue);
        else if(pressY > y)
            putRectFrame(pressX, y, x - pressX, pressY - y ,&im , red, green, blue);
        else
            putRectFrame(pressX, pressY, x - pressX, y - pressY,&im, red, green, blue);
    }

    //Rysowanie lini gorszy algorytm
    else if(wybor == "Linia1"){
        //im.fill(Qt::black);
        im = copy;
        putLineVol1(pressX, pressY, x, y, &im, red, green, blue);
    }

    //Rysowanie lini lepszy algorytm
    else if(wybor == "Linia2"){
        //im.fill(Qt::black);
        im = copy;
        putLineVol2(pressX, pressY, x, y, &im, red, green, blue);
    }

    //rysowanie pikseli w formie spraya w petli gestosc spraya, rozpietosc przy rand()
    else if(wybor == "Spray"){
        for(int i = 0; i < 100 ; i++){
            putPixel(x + rand()%spraySize, y+rand()%spraySize, &im, red, green, blue);
        }
    }

    else if(wybor == "Okrag"){
        im = copy;
        int R = int( sqrt((x-pressX)*(x-pressX) + (y-pressY) * (y-pressY)) );
        putCirclevol1(pressX, pressY, R, &im, red, green, blue);
        //qDebug("%d %d", pressX, pressY);
        //putCirclevol1(123, 123, 100, &im, red, green, blue);
    }

    else if (wybor == "Elipsa") {
        im = copy;
        elipseBeta = 0;
        elipseY0 = (y + pressY)/2;
        elipseX0 = (x + pressX)/2;
        elipseR1 = (pressX - x)/2;
        elipseR2 = (pressY - y)/2;
        putElipse(elipseX0, elipseY0, elipseR1, elipseR2, elipseBeta, &im, red, green, blue);
    }

    update();
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    if(wybor == "FloodFill"){
        QPoint p = QPoint(e->x(), e->y());
        floodFill(p, im.pixel(p.x(), p.y()), fillColor.rgb(), &im);
        update();
    }

    if(wybor == "ScanLine"){
        QPoint p = QPoint(e->x(), e->y());
        putDot(p.x(), p.y(), &im, red, green, blue);
        scanLinePoints.push_back(p);
        update();
    }

    if(e->button() == Qt::LeftButton){
        pressX = e->x();
        pressY = e->y();
        copy = im;
    }
}

//rysowanie jednego pixela o kolorze rgb na obrazku imag
void MyWidget::putPixel(int x, int y, QImage *imag, int r, int g, int b)
{
    if( y >= 0 && x >= 0 && x < imag->width() && y < imag->height()){
        uchar *p = imag->scanLine(y);
        p[x*4] = uchar(b);
        p[x*4 + 1] = uchar(g);
        p[x*4 + 2] = uchar(r);
        // r = r < 0: r > 255 ? 255 : r; ustawienie satruracji w przypadku złych wartosci r, g, b
    }
}

//rysowanie prostokat od (x,y) szeroksoci width i wysokosci height o kolorze rgb na obrazki imag
void MyWidget::putRect(int x, int y, int width, int height, QImage *imag, int r, int g, int b)
{
    for(int i=x; i <= x + width; i++){
        for(int j=y; j<= y + height; j++){
            putPixel(i, j, imag, r, g, b);
        }
    }

    //prawdopodobnie lepsza wersja rysowania prostokata
    /*for(int i = y; i <= y + height; i++){
        if(y >= 0 && y < imag->height()){
            uchar *p = imag->scanLine(i);
            for(int j = x; j < x + width; j++){
                if(x >= 0 && x <= imag->width()){
                    p[j*4] = uchar(b);
                    p[j*4 + 1] = uchar(g);
                    p[j*4 + 2] = uchar(r);
                }
            }
        }
    }*/
}

//rysowanie ramki prostokata od (x,y) szerokosci width i wysoskosci height o kolorze rgb na obrazku imag
void MyWidget::putRectFrame(int x, int y, int width, int height, QImage *imag, int r, int g, int b)
{
    for(int i=x; i <= x + width; i++){
        for(int j=y; j<= y + height; j++){
            if(i == x || i == x + width)
                putPixel(i, j, imag, r, g, b);
            else if(j == y || j == y + height)
                putPixel(i, j, imag, r, g, b);
            // Wypelnianie wnetrza
            /*else
                putPixel(i, j, imag, 255, 255, 255);*/
        }
    }
}

//rysowanie lini pomiedzy (x1,y1), a (x2,y2) o kolrze rgb na obrazku imag
void MyWidget::putLineVol1(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b)
{
    float t, l;
    int x, y;
    l = float(sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)) + 1);

    for(int i = 0; i <= l; i++){
        t = i / l;
        x = int(x1 + t * (x2 - x1));
        y = int(y1 + t * (y2 - y1));
        putPixel(x, y, imag, r, g, b);
    }
}

//rysowanie lini pomiedzy (x1,y1), a (x2,y2) o kolrze rgb na obrazku imag
void MyWidget::putLineVol2(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b)
{
    int y, x, dy, dx;
    float t;
    dx = abs(x2-x1);
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

void MyWidget::putCirclevol1(int x0, int y0, int R, QImage *imag, int r, int g, int b)
{
    int y;
    int a = int(R/sqrt(2));
    for(int x=0; x <= a; x++){
        y = int(sqrt(R*R - x*x));
        putPixel(x+x0, y+y0, imag, r, g, b);
        putPixel(x+x0, -y+y0, imag, r, g, b);
        putPixel(-x+x0, y+y0, imag, r, g, b);
        putPixel(-x+x0, -y+y0, imag, r, g, b);
        putPixel(y+x0, x+y0, imag, r, g, b);
        putPixel(y+x0, -x+y0, imag, r, g, b);
        putPixel(-y+x0, x+y0, imag, r, g, b);
        putPixel(-y+x0, -x+y0, imag, r, g, b);
    }
}

void MyWidget::putElipse(int x0, int y0, int r1, int r2, double beta, QImage *imag, int r, int g, int b)
{
    int x, finalX, startX = 0, previousX = 0, y, finalY, previousY = 0, startY = 0, N = 20;
    double alfa;
    isPaintedElipse = true;

    for(int i = 0; i < N; i++){
        alfa = i*2*M_PI/double(N);
        x = int(r1 * std::cos(alfa));
        y = int(r2 * std::sin(alfa));
        finalX = int(std::cos(beta) * x  - std::sin(beta) * y + x0);
        finalY = int(std::sin(beta) * x  + std::cos(beta) * y + y0);
        putPixel(finalX, finalY, imag, r, g, b);

        if(i == 0){
            startX = finalX;
            startY = finalY;
        }
        else if(i == N-1){
            putLineVol2(startX, startY, finalX, finalY, imag, r, g, b);
            putLineVol2(finalX, finalY, previousX, previousY, imag, r, g, b);
        }
        else if(i > 0 ){
            putLineVol2(finalX, finalY, previousX, previousY, imag, r, g, b);
        }

        previousY = finalY;
        previousX = finalX;
    }
}

void MyWidget::floodFill(QPoint p, QRgb currentColor, QRgb newColor, QImage *imag)
{
    std::stack<QPoint> stack;
    if(currentColor == newColor){
        qDebug("Te same kolory!");
        return;
    }
    if(imag->pixel(p) != currentColor)
        return;
    stack.push(p);
    while(!stack.empty()){
        QPoint temp = stack.top();
        stack.pop();
        if((imag->pixel(temp) == currentColor)){
            int w = temp.x(), e = temp.x(), y = temp.y();
            while((w >= 0) && (imag->pixel(QPoint(w, y)) == currentColor))w--;
            while((e < imag->width()) && (imag->pixel(QPoint(e, y)) == currentColor))e++;
            for(int i=w+1; i < e; i++){
                imag->setPixel(i, y, newColor);
            }
            for(int i=w+1; i < e; i++){
                if(y != imag->height()-1)
                    if(imag->pixel(i, y+1) == currentColor) stack.push(QPoint(i, y+1));
                if(y != 0)
                    if(imag->pixel(i, y-1) == currentColor) stack.push(QPoint(i, y-1));
            }
        }
    }
}

void MyWidget::scanLine(std::vector<QPoint> polygon)
{
    int yMin, yMax, x;
    QPoint prev;
    struct krawedz{
        QPoint poczatek, koniec;
    };
    std::vector<krawedz> krawedzie;
    std::vector<int> przeciecia;

    yMax = yMin = polygon[0].y();
    prev = polygon[0];

    for(std::size_t i = 1; i < polygon.size(); i++){
        if(polygon[i].y() > yMax) yMax = polygon[i].y();
        if(polygon[i].y() < yMin) yMin = polygon[i].y();
        krawedzie.push_back(krawedz({prev, polygon[i]}));
        //putLineVol2(prev.x(), prev.y(), polygon[i].x(), polygon[i].y(), &im, 0, 255, 0);
        prev = polygon[i];
    }

    krawedzie.push_back(krawedz({prev, polygon[0]}));

    for(int y=yMin; y<=yMax; y++){
        for(krawedz k: krawedzie){
            if( k.poczatek.y() < k.koniec.y() ){
                if(k.poczatek.y() <= y && k.koniec.y() >= y){
                    int a = k.koniec.x() - k.poczatek.x();
                    int b = k.koniec.y() - k.poczatek.y();
                    int c = y - k.poczatek.y();
                    if(y != k.koniec.y()){
                        x = int(k.poczatek.x() + float(a*c/b));
                        przeciecia.push_back(x);
                    }
                }
            }
            else if(k.koniec.y() < k.poczatek.y()){
                if(k.poczatek.y() >= y && k.koniec.y() <= y){
                    int a = k.poczatek.x() - k.koniec.x();
                    int b = k.poczatek.y() - k.koniec.y();
                    int c = y - k.koniec.y();
                    if(y != k.poczatek.y()){
                        x = int(k.koniec.x() + float(a*c/b));
                        przeciecia.push_back(x);
                    }
                }
            }

        }
        sort(przeciecia.begin(), przeciecia.end());

        for(std::size_t i=0; i < przeciecia.size(); i+=2){
            for(int j=przeciecia[i]; j< przeciecia[i+1]; j++){
                putPixel(j, y, &im, red, green, blue);
            }
        }
        przeciecia.clear();
    }
}

void MyWidget::setIsPaintedElipse(bool value)
{
    isPaintedElipse = value;
}

bool MyWidget::getIsPaintedElipse() const
{
    return isPaintedElipse;
}

void MyWidget::setElipseBeta(double value)
{
    elipseBeta = value;
}

void MyWidget::paintRotatedElipse()
{
    im = copy;
    putElipse(elipseX0, elipseY0, elipseR1, elipseR2, elipseBeta, &im, red, green, blue);
    update();
}

void MyWidget::setSpraySize(int value)
{
    spraySize = value;
}

void MyWidget::clearIm()
{
    im.fill(Qt::black);
}

void MyWidget::setWybor(const QString &value)
{
    wybor = value;
}

//rysowanie jednego pixela o kolorze rgb na obrazku imag
void MyWidget::putDot(int x, int y, QImage *imag, int r, int g, int b)
{
    for(int i = x-3; i <= x+3; i++){
        for(int j = y-3; j < y+3; j++){
            if((i-x)*(i-x) + (j-y)*(j-y) <= 9)
            putPixel(i,j,imag,r,g,b);
        }
    }
}
