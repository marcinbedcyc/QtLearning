#include "mywidget.h"

#include <QPainter>

myWidget::myWidget(QWidget *parent) : QWidget(parent)
{
    im  = QImage(900, 600, QImage::Format_RGB32);
    im.fill(Qt::black);
    red = green = blue = 255;
    kursor.setShape(Qt::ArrowCursor);
    setCursor(kursor);
    setMouseTracking(true);
    changePoints = pointSelected = false;
//    QPoint p1 = QPoint(200, 200);
//    QPoint p2 = QPoint(300, 100);
//    QPoint p3 = QPoint(400, 100);
//    QPoint p4 = QPoint(500, 250);
//    putDot(p1.x(), p1.y(), &im, 255, 0, 0);
//    putDot(p2.x(), p2.y(), &im, 255, 0, 0);
//    putDot(p3.x(), p3.y(), &im, 255, 0, 0);
//    putDot(p4.x(), p4.y(), &im, 255, 0, 0);
//    putBSpline(p1,p2,p3,p4, &im, 255, 255, 255);
}

void myWidget::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.drawImage(0, 0, im);
}

// Changing between bezier and bspline by comment and uncomment drawing methods
void myWidget::mousePressEvent(QMouseEvent *m){
    int x, y;
    x = m->x();
    y = m->y();

    if(!changePoints){
        if(m->button() == Qt::LeftButton){
            punkty.push_back(QPoint(x,y));
            //putKrzyweBeziera(punkty, &im, red, green, blue);
            putBsplines(punkty, &im, red, green, blue);
        }
        else if(m->button() == Qt::RightButton){
            for (QPoint p: punkty){
                if((x-p.x())*(x-p.x()) + (y-p.y())*(y-p.y()) <= 25){
                    punkty.remove(p);
                    qDebug("Usuneicie %d", int(punkty.size()));
                    im.fill(Qt::black);
                    //putKrzyweBeziera(punkty, &im, red, green, blue);
                    putBsplines(punkty, &im, red, green, blue);
                    break;
                }
            }
        }
    }
    else{
        for (QPoint p : punkty){
            if((x-p.x())*(x-p.x()) + (y-p.y())*(y-p.y()) <= 25){
                pointToChange = std::find(punkty.begin(), punkty.end(), p);
                pointSelected = true;
                qDebug("Chosen! %d %d", p.x(), p.y());
                break;
            }
        }
    }
}

void myWidget::mouseMoveEvent(QMouseEvent *m)
{
    int x,y;

    x = m->x();
    y = m->y();

    if(!changePoints){
        kursor.setShape(Qt::ArrowCursor);
        setCursor(kursor);

        for (QPoint p : punkty){
            if((x-p.x())*(x-p.x()) + (y-p.y())*(y-p.y()) <= 25){
                qDebug("Inside Dot %d %d",p.x(), p.y());
                kursor.setShape(Qt::PointingHandCursor);
                setCursor(kursor);
                break;
            }
        }
    }
    else{
        if(pointSelected){
            qDebug("Change!");
            if(x >=0 && y >= 0 && x < width() && y < height()){
                pointToChange->setX(x);
                pointToChange->setY(y);
            }
            im.fill(Qt::black);
            //putKrzyweBeziera(punkty, &im, red, green, blue);
            putBsplines(punkty, &im, red, green, blue);
        }
    }
}

void myWidget::mouseReleaseEvent(QMouseEvent*)
{
    if(changePoints && pointSelected){
        pointSelected = false;
    }
}

//rysowanie jednego pixela o kolorze rgb na obrazku imag
void myWidget::putPixel(int x, int y, QImage *imag, int r, int g, int b)
{
    if( y >= 0 && x >= 0 && x < imag->width() && y < imag->height()){
        uchar *p = imag->scanLine(y);
        p[x*4] = uchar(b);
        p[x*4 + 1] = uchar(g);
        p[x*4 + 2] = uchar(r);
    }
}

//rysowanie jednego pixela o kolorze rgb na obrazku imag
void myWidget::putDot(int x, int y, QImage *imag, int r, int g, int b)
{
    for(int i = x-5; i <= x+5; i++){
        for(int j = y-5; j < y+5; j++){
            if((i-x)*(i-x) + (j-y)*(j-y) <= 25)
            putPixel(i,j,imag,r,g,b);
        }
    }
}

void myWidget::putKrzyweBeziera(std::list<QPoint> punkty, QImage *imag, int r, int g, int b)
{
    if(punkty.size() >= 4){
        std::list<QPoint>::iterator it = punkty.begin();
        int licznik = 0;
        QPoint p1, p2, p3, p0;
        p0 = *it;
        it++;
        p1 = *it;
        it++;
        p2 = *it;
        it++;
        p3 = *it;
        qDebug("(%d,%d) (%d,%d) (%d,%d) (%d,%d)", p0.x(), p0.y(), p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y());
        putKrzywaBeziera(p0, p1, p2, p3, &im, r, g, b);
        licznik = 6;
        while( licznik < int(punkty.size())){
            p0 = *it;
            it++;
            p1 = *it;
            it++;
            p2 = *it;
            it++;
            p3 = *it;
            qDebug("(%d,%d) (%d,%d) (%d,%d) (%d,%d)", p0.x(), p0.y(), p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y());
            putKrzywaBeziera(p0, p1, p2, p3, &im, red, green, blue);
            licznik += 3;
        }
    }
    putDots(punkty, imag, 0, 255, 0);
    update();
}

void myWidget::putBsplines(std::list<QPoint> punkty, QImage *imag, int r, int g, int b)
{
    if(punkty.size() >= 4){
        int length = int(punkty.size());
        int *prevX, *prevY;
        prevX = new int;
        prevY = new int;
        QPoint p1, p2, p3, p0;
        std::list<QPoint>::iterator it = punkty.begin();
        for(int j=0; j <= length - 4; j++){
            p0 = *it;
            it++;
            p1 = *(it);
            it++;
            p2 = *(it);
            it++;
            p3 = *(it);
            qDebug("(%d,%d) (%d,%d) (%d,%d) (%d,%d)", p0.x(), p0.y(), p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y());
            if(j == 0)
                putBSpline(p0, p1, p2, p3, imag, r, g, b, prevX, prevY, false );
            else {
                putBSpline(p0, p1, p2, p3, imag, r, g, b, prevX, prevY, true );
            }
            it--;
            it--;
        }
    }
    putDots(punkty, imag, 0, 255, 0);
    update();
}

void myWidget::putDots(std::list<QPoint> punkty, QImage *imag, int r, int g, int b)
{
    for(QPoint p:punkty){
        putDot(p.x(), p.y(), imag, r, g ,b);
    }
}

void myWidget::setChangePoints(bool value)
{
    changePoints = value;
}

//rysowanie lini pomiedzy (x1,y1), a (x2,y2) o kolrze rgb na obrazku imag
void myWidget::putLine(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b)
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

//rysowanie krzywej Beziera dla punktow p0, p1, p2, p3, p4 na obrazku imag o kolorze rgb
void myWidget::putKrzywaBeziera(QPoint p0, QPoint p1, QPoint p2, QPoint p3, QImage *imag, int r, int g, int b)
{
    int x, prevX=0, y, prevY=0, N = 20;
    double t;
    for(int i = 0; i <= N; i++){
        t = i/ double(N);
        x = int((1-t)*(1-t)*(1-t)*p0.x() + 3*(1-t)*(1-t)*t*p1.x() + 3*(1-t)*t*t*p2.x() + t*t*t*p3.x());
        y = int((1-t)*(1-t)*(1-t)*p0.y() + 3*(1-t)*(1-t)*t*p1.y() + 3*(1-t)*t*t*p2.y() + t*t*t*p3.y());
        if(i != 0)
            putLine(x ,y ,prevX, prevY, imag, r, g, b);
        prevX = x;
        prevY = y;
    }
}

//rysowanie krzywej B-Spline dla punktow p0, p1, p2, p3, p4 na obrazku imag i kolorze rgb
void myWidget::putBSpline(QPoint p0, QPoint p1, QPoint p2, QPoint p3, QImage *imag, int r, int g, int b, int *prX, int *prY, bool prev)
{
    int x, prevX = 0, y, prevY = 0, N = 30;
    double t;
    for(int i = 0; i < N; i++){
        t = i / double(N);
        //qDebug("%f", t);
        x = patternBSplineX(p0, p1, p2, p3, t);
        y = patternBSplineY(p0, p1, p2, p3, t);


        if(i == 0 && prev ){
            prevX = *prX;
            prevY = *prY;
            putLine(x ,y ,prevX, prevY, imag, r, g, b);
        }
        else if(i != 0)
            putLine(x ,y ,prevX, prevY, imag, r, g, b);
        *prX = prevX = x;
        *prY = prevY = y;
    }
}

int myWidget::patternBSplineX(QPoint &p0, QPoint &p1, QPoint &p2, QPoint &p3, double t)
{
    double result = (1.0/6.0)*(-1*t*t*t+3.0*t*t+(-3.0)*t+1.0)*p0.x() + (1.0/6.0)*(3.0*t*t*t+(-6.0)*t*t+4.0)*p1.x() +
                (1.0/6.0)*((-3.0)*t*t*t+3.0*t*t+3.0*t+1.0)*p2.x() + (1.0/6.0)*t*t*t*p3.x();
    return int(result);
}

int myWidget::patternBSplineY(QPoint &p0, QPoint &p1, QPoint &p2, QPoint &p3, double t)
{
    double result = (1.0/6.0)*(-1*t*t*t+3.0*t*t+(-3.0)*t+1.0)*p0.y() + (1.0/6.0)*(3.0*t*t*t+(-6.0)*t*t+4.0)*p1.y() +
                (1.0/6.0)*((-3.0)*t*t*t+3.0*t*t+3.0*t+1.0)*p2.y() + (1.0/6.0)*t*t*t*p3.y();
    return int(result);
}


