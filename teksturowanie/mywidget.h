#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void resetuj();
    void setChangePoints(bool);
private:
    QImage texture, triangle, orginalTexture;
    std::vector<QPoint> texturePoints;
    std::vector<QPoint> trianglePoints;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void putTriagle(std::vector<QPoint> &, QImage *);
    void putLineVol2(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b);
    void putDot(int x, int y, QImage *imag, int r, int g, int b);
    void putPixel(int x, int y, QImage *imag, int r, int g, int b);
    void teksturuj(std::vector<QPoint> &, std::vector<QPoint> &);
    int licznikTexture, licznikTriangle;
    bool pointSelected,pointSelectedT, changePoints;
    std::vector<QPoint>::iterator pointToChange;


signals:

public slots:
};

#endif // MYWIDGET_H
