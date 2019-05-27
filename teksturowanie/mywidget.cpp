#include "mywidget.h"

#include <QPaintEvent>
#include <QPainter>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    triangle = QImage(650, 500, QImage::Format_RGB32);
    texture = QImage(650, 500, QImage::Format_RGB32);
    orginalTexture = QImage("/home/marcin/Dokumenty/studia/Semestr IV/LGiM/teksturowanie/images/face.png");
    resetuj();
}

void MyWidget::resetuj()
{
    trianglePoints.clear();
    texturePoints.clear();
    triangle.fill(Qt::black);
    licznikTexture = licznikTriangle = 0;
    texture = orginalTexture;
}

void MyWidget::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0, 0, triangle);
    p.drawImage(750, 0, texture);
}

void MyWidget::mousePressEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();

    if(!changePoints){
        if(x < 650 && y < 750 && x >= 0 && y >=0 && licznikTriangle < 3){
            putDot(x, y, &triangle, 0, 255, 0);
            trianglePoints.push_back(QPoint(x,y));
            licznikTriangle++;
        }

        if(x >= 750 && y < 750 && x < 1400 && y >=0 && licznikTexture < 3){
            x = x - 750;
            putDot(x, y, &texture, 0, 255, 0);
            texturePoints.push_back(QPoint(x,y));
            licznikTexture++;
        }

        if(licznikTriangle == 3)
            putTriagle(trianglePoints, &triangle);

        if(licznikTexture == 3)
            putTriagle(texturePoints, &texture);

        if(licznikTexture == 3 && licznikTriangle == 3){
            teksturuj(trianglePoints, texturePoints);
        }
        update();
    }
    else{
        for(QPoint p: trianglePoints){
            if((x-p.x())*(x-p.x()) + (y-p.y())*(y-p.y()) <= 25){
                pointToChange = std::find(trianglePoints.begin(), trianglePoints.end(), p);
                pointSelected = true;
                qDebug("Chosen! %d %d", p.x(), p.y());
                return;
            }
        }
        for(QPoint p: texturePoints){
            if((x-750-p.x())*(x-750-p.x()) + (y-p.y())*(y-p.y()) <= 25){
                pointToChange = std::find(texturePoints.begin(), texturePoints.end(), p);
                pointSelectedT = true;
                qDebug("Chosen! %d %d", p.x(), p.y());
                return;
            }
        }
    }
}

void MyWidget::mouseMoveEvent(QMouseEvent *m)
{
    int x,y;

    x = m->x();
    y = m->y();

    if(pointSelected){
        qDebug("Change!");
        if(x >=0 && y >= 0 && x < triangle.width() && y < triangle.height()){
            pointToChange->setX(x);
            pointToChange->setY(y);
        }
        triangle.fill(Qt::black);
        for(QPoint p : trianglePoints){
            putDot(p.x(), p.y(), &triangle, 0, 255, 0);
        }

        if(licznikTriangle == 3)
            putTriagle(trianglePoints, &triangle);

        if(licznikTexture == 3 && licznikTriangle == 3){
            teksturuj(trianglePoints, texturePoints);
        }
    }
    if(pointSelectedT){
        qDebug("Change!");
        if(x >= texture.width()+100 && y >= 0 && x < texture.width() + 750 && y < texture.height()){
            pointToChange->setX(x-750);
            pointToChange->setY(y);
        }
        texture = orginalTexture;
        for(QPoint p : texturePoints){
            putDot(p.x(), p.y(), &texture, 0, 255, 0);
        }
        if(licznikTexture == 3)
            putTriagle(texturePoints, &texture);
        if(licznikTexture == 3 && licznikTriangle == 3){
            teksturuj(trianglePoints, texturePoints);
        }
    }
    update();
}

void MyWidget::mouseReleaseEvent(QMouseEvent*)
{
    if(changePoints && pointSelected){
        pointSelected = false;
    }
    if(changePoints && pointSelectedT){
        pointSelectedT = false;
    }
}

void MyWidget::putTriagle(std::vector<QPoint> &points, QImage *image)
{
    putLineVol2(points[0].x(), points[0].y(),points[1].x(), points[1].y(), image, 255, 255, 255);
    putLineVol2(points[1].x(), points[1].y(),points[2].x(), points[2].y(), image, 255, 255, 255);
    putLineVol2(points[2].x(), points[2].y(),points[0].x(), points[0].y(), image, 255, 255, 255);
}

void MyWidget::teksturuj(std::vector<QPoint> &vec, std::vector<QPoint> &textureV)
{
    //qDebug("%d %d %d %d %d %d", textureV[0].x(), textureV[0].y(), textureV[1].x(), textureV[1].y(), textureV[2].x(), textureV[2].y());
    //qDebug("%d %d %d %d %d %d", vec[0].x(), vec[0].y(), vec[1].x(), vec[1].y(), vec[2].x(), vec[2].y());
    double mianownik = ( (vec[1].x() - vec[0].x()) * (vec[2].y() - vec[0].y()) ) - ( (vec[2].x() - vec[0].x()) *
            (vec[1].y() - vec[0].y()));

    int yMin, yMax, x,xT, yT;
    double u, v, w;
    QPoint prev;
    struct krawedz{
        QPoint poczatek, koniec;
    };
    std::vector<krawedz> krawedzie;
    std::vector<int> przeciecia;

    yMax = yMin = vec[0].y();
    prev = vec[0];

    for(std::size_t i = 1; i < vec.size(); i++){
        if(vec[i].y() > yMax) yMax = vec[i].y();
        if(vec[i].y() < yMin) yMin = vec[i].y();
        krawedzie.push_back(krawedz({prev, vec[i]}));
        prev = vec[i];
    }

    krawedzie.push_back(krawedz({prev, vec[0]}));

    for(int y = yMin; y <= yMax; y++){
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

        for(std::size_t i = 0; i < przeciecia.size(); i += 2){
            for(int j = przeciecia[i]; j < przeciecia[i+1]; j++){
                if(mianownik != 0){
                    v = ( ((j - vec[0].x()) * (vec[2].y() - vec[0].y()) ) - ( (vec[2].x() - vec[0].x()) * (y - vec[0].y()) ) ) / mianownik;
                    w = ( ((vec[1].x() - vec[0].x()) * (y - vec[0].y())) - ((j - vec[0].x()) * (vec[1].y() - vec[0].y())) ) / mianownik;
                    u = 1 - v - w;
                    //qDebug("%f %f %f", u , v, w);
                    xT = int(u * textureV[0].x() + v * textureV[1].x() + w * textureV[2].x());
                    yT = int(u * textureV[0].y() + v * textureV[1].y() + w * textureV[2].y());
                    triangle.setPixel(j, y, orginalTexture.pixel(xT, yT));
                    //triangle.setPixel(j, y, QColor(Qt::white).rgb());
                }
            }
        }
        przeciecia.clear();
    }

}

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

void MyWidget::putPixel(int x, int y, QImage *imag, int r, int g, int b){
    if( y >= 0 && x >= 0 && x < imag->width() && y < imag->height()){
        uchar *p = imag->scanLine(y);
        p[x*4] = uchar(b);
        p[x*4 + 1] = uchar(g);
        p[x*4 + 2] = uchar(r);
    }
}

void MyWidget::putDot(int x, int y, QImage *imag, int r, int g, int b){
    for(int i = x-3; i <= x+4; i++){
        for(int j = y-3; j < y+4; j++){
            if((i-x)*(i-x) + (j-y)*(j-y) <= 16)
                putPixel(i,j,imag,r,g,b);
        }
    }
}

void MyWidget::setChangePoints(bool value)
{
    changePoints = value;
}

