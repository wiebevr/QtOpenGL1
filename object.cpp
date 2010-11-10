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

void Object::setPosition(QVector3D position)
{
    _position = position;
    _positionMatrix.setToIdentity();
    _positionMatrix.translate(position);
}

void Object::setYRotation(double yRotation)
{
    _yRotation = yRotation;
    _positionMatrix.setToIdentity();
    _positionMatrix.rotate(yRotation, QVector3D(0.0f, 1.0f, 0.0f));
}

QVector3D Object::getPosition() const
{
    return _position;
}

double Object::getYRotation() const
{
    return _yRotation;
}
