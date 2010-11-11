#include "object.h"
#include <QDebug>

Object::Object(QObject *parent)
    : QObject(parent)
{
    _scale = QVector3D(1.0f, 1.0f, 1.0f);
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

void Object::updatePositionMatrix()
{
    _positionMatrix.setToIdentity();
    _positionMatrix.rotate(_rotation.x(), QVector3D(1.0f, 0.0f, 0.0f));
    _positionMatrix.rotate(_rotation.y(), QVector3D(0.0f, 1.0f, 0.0f));
    _positionMatrix.rotate(_rotation.z(), QVector3D(0.0f, 0.0f, 1.0f));
    _positionMatrix.translate(_position);
    _positionMatrix.scale(_scale);
}

void Object::setPosition(QVector3D position)
{
    _position = position;
    updatePositionMatrix();
}

QVector3D Object::getPosition() const
{
    return _position;
}

void Object::setRotation(QVector3D rotation)
{
    _rotation = rotation; 
    updatePositionMatrix();
}

QVector3D Object::getRotation() const
{
    return _rotation;
}

void Object::setScale(QVector3D scale)
{
    _scale = scale;
    updatePositionMatrix();
}

QVector3D Object::getScale() const
{
    return _scale;
}

void Object::setYRotation(double yRotation)
{
    _rotation.setY(yRotation);
    updatePositionMatrix();
}

double Object::getYRotation() const
{
    return _rotation.y();
}

void Object::setXRotation(double xRotation)
{
    _rotation.setX(xRotation);
    updatePositionMatrix();
}

double Object::getXRotation() const
{
    return _rotation.x();
}

void Object::setZRotation(double zRotation)
{
    _rotation.setZ(zRotation);
    updatePositionMatrix();
}

double Object::getZRotation() const
{
    return _rotation.z();
}
