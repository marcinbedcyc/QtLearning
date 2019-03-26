#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QPaintEvent>
#include <QWidget>
#include <algorithm>

class myWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myWidget(QWidget *parent = nullptr);

    void setChangePoints(bool value);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *m);
    void mouseMoveEvent(QMouseEvent *m);
    void mouseReleaseEvent(QMouseEvent *m);
    void putPixel(int x, int y, QImage *imag, int r, int g, int b);
    void putKrzywaBeziera(QPoint p0, QPoint p1, QPoint p2, QPoint p3, QImage *imag, int r, int g, int b);
    void putBSpline(QPoint p0, QPoint p1, QPoint p2, QPoint p3, QImage *imag, int r, int g, int b,  int *prX, int *prY, bool prev);
    int patternBSplineX(QPoint &p0, QPoint &p1, QPoint &p2, QPoint &p3, double t);
    int patternBSplineY(QPoint &p0, QPoint &p1, QPoint &p2, QPoint &p3, double t);
    void putLine(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b);
    void putDot(int x, int y, QImage *imag, int r, int g, int b);
    void putKrzyweBeziera(std::list<QPoint> punkty, QImage *imag, int r, int g, int b);
    void putBsplines(std::list<QPoint> punkty, QImage *imag, int r, int g, int b);
    void putDots(std::list<QPoint> punkty, QImage *imag, int r, int g, int b);

private:
    QImage im,copy;
    int red, green, blue;
    std::list<QPoint> punkty;
    std::list<QPoint>::iterator pointToChange;
    QCursor kursor;
    bool pointSelected, changePoints;

signals:

public slots:
};

#endif // MYWIDGET_H
