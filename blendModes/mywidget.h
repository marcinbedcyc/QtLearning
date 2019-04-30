#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "layer.h"

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
    QImage image;
    Layer layers[3];
    void paintEvent(QPaintEvent *);
    QImage alphaBlending(QImage *, QImage *, int alfa);
    QImage normalBlend(QImage *, QImage *);
    QImage averageBlend(QImage *, QImage *);
    QImage multiplyBlend(QImage *, QImage *);
    QImage screenBlend(QImage *, QImage *);
    QImage darkenBlend(QImage *, QImage *);
    QImage lightenBlend(QImage *, QImage *);
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void mixLayers();
    Layer* getLayer(int index);

signals:

public slots:
};

#endif // MYWIDGET_H
