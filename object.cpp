#include "object.h"
#include <QDebug>

Object::Object(QObject *parent)
    : QObject(parent)
{
}

Object::~Object()
{
}

QMatrix4x4 Object::getPositionMatrix() const
{
    return _positionMatrix;
}

void Object::setPositionMatrix(QMatrix4x4 positionMatrix)
{
    _positionMatrix = positionMatrix;
}
