#include "layer.h"

QImage Layer::getImage() const
{
    return image;
}

void Layer::setImage(const QImage &value)
{
    image = value;
}

int Layer::getAlfa() const
{
    return alfa;
}

void Layer::setAlfa(int value)
{
    alfa = value;
}

QString Layer::getBlendMode() const
{
    return blendMode;
}

void Layer::setBlendMode(const QString &value)
{
    blendMode = value;
}

Layer::Layer()
{

}

Layer::Layer(QImage image, int alfa, QString blendMode)
{
    this->image = image;
    this->alfa = alfa;
    this->blendMode = blendMode;
}
