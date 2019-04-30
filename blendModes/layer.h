#ifndef LAYER_H
#define LAYER_H

#include <QImage>

class Layer
{
private:
    int alfa;
    QString blendMode;
public:
    Layer();
    Layer(QImage image, int alfa, QString blendMode);
    QImage image;
    QImage getImage() const;
    void setImage(const QImage &value);
    int getAlfa() const;
    void setAlfa(int value);
    QString getBlendMode() const;
    void setBlendMode(const QString &value);
};

#endif // LAYER_H
