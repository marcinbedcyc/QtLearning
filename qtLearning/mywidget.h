#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QPaintEvent>
#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    int  red, green, blue;
    QColor fillColor;
    std::vector<QPoint> scanLinePoints;
    void setWybor(const QString &value);
    void clearIm();
    void setSpraySize(int value);
    void setElipseBeta(double value);
    void paintRotatedElipse();
    bool getIsPaintedElipse() const;
    void setIsPaintedElipse(bool value);
    void scanLine(std::vector<QPoint> polygon);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void putPixel(int x, int y, QImage *imag, int r, int g, int b);
    void putRect(int x, int y, int width, int height, QImage *imag, int r, int g, int b);
    void putRectFrame(int x, int y, int width, int height, QImage *imag, int r, int g, int b);
    void putLineVol1(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b);
    void putLineVol2(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b);
    void putCirclevol1(int x0, int y0, int R, QImage *imag, int r, int g, int b);
    void putElipse(int x0, int y0, int r1, int r2, double beta, QImage *imag, int r, int g, int b);
    void floodFill(QPoint p, QRgb currentColor, QRgb newColor, QImage *imag);
    void putDot(int x, int y, QImage *imag, int r, int g, int b);

private:
    QImage im, copy;
    int pressX, pressY, spraySize, elipseX0, elipseY0, elipseR1, elipseR2;
    double elipseBeta;
    QString wybor;
    bool isPaintedElipse;

signals:

public slots:
};

#endif // MYWIDGET_H
