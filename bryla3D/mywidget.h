#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMatrix4x4>
#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
    QImage image;
    int red, green, blue;
    QMatrix4x4 center, reverseCenter;
    QVector<QVector3D> orginalImage, resultImage;
    QVector<QPoint> imageToDraw;
    void paintEvent(QPaintEvent *);
    void putPixel(int x, int y, QImage *imag, int r, int g, int b);
    void putLineVol2(int x1, int y1, int x2, int y2, QImage *imag, int r, int g, int b);
    void rzutRownolegly();
    void rzutPerspektywiczny();
    bool isPerspective;
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void drawPicture();
    QMatrix4x4 transformation;

    bool getIsPerspective() const;
    void setIsPerspective(bool value);

signals:

public slots:
};

#endif // MYWIDGET_H
