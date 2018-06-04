#include "virus.h"

Virus::Virus(QObject *parent)
    : QObject(parent)
    , _radius(10)
{
    QRandomGenerator random = QRandomGenerator();
    _x = random.bounded(500);
    _y = random.bounded(500);
}

int Virus::get_x()
{
    return _x;
}

int Virus::get_y()
{
    return _y;
}

int Virus::get_radius()
{
    return _radius;
}
