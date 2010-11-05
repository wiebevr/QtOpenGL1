#include "object.h"
#include <QDebug>

Object::Object(QObject *parent)
    : QObject(parent)
{
}

Object::~Object()
{
}

QGLShader *Object::getVertexShader() const
{
    return _vertexShader;
}

QGLShader *Object::getFragmentShader() const
{
    return _fragmentShader;
}

QGLBuffer Object::getVertexBuffer() const
{
    return _vertexBuffer;
}

QGLBuffer Object::getElementBuffer() const
{
    return _elementBuffer;
}

QMatrix4x4 Object::getPositionMatrix() const
{
    return _positionMatrix;
}

void Object::setPositionMatrix(QMatrix4x4 positionMatrix)
{
    _positionMatrix = positionMatrix;
}
