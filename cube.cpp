#include "cube.h"
#include <QDebug>

Cube::Cube(QObject *parent)
    : QObject(parent)
{
    // Timer:
    _timer = new QTimer(this);
    _timer->start(10);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    // Matrix:
    _worldMatrix.setToIdentity();
    //_worldMatrix.translate(1.0f, 1.0f, 0.0f);
}

Cube::~Cube()
{
}

QGLShader *Cube::getVertexShader() const
{
    return _vertexShader;
}

QGLShader *Cube::getFragmentShader() const
{
    return _fragmentShader;
}

const QVector<QVector3D> &Cube::getVertexData() const
{
    return _vertexData;
}

QGLBuffer Cube::getVertexBuffer() const
{
    return _vertexBuffer;
}

QGLBuffer Cube::getElementBuffer() const
{
    return _elementBuffer;
}

QMatrix4x4 Cube::getWorldMatrix() const
{
    return _worldMatrix;
}

void Cube::setWorldMatrix(QMatrix4x4 worldMatrix)
{
    _worldMatrix = worldMatrix;
}

void Cube::timeout()
{
    //_worldMatrix.rotate(1.0f, 1.0f, 0.0f, 0.0f);
}

void Cube::makeResources()
{
    makeGeometry();
    makeShaders();
}

void Cube::makeShaders()
{
    _vertexShader = new QGLShader(QGLShader::Vertex, this);
    _fragmentShader = new QGLShader(QGLShader::Fragment, this);
    
    _vertexShader->compileSourceFile(":/shaders/shader.v.glsl");
    _fragmentShader->compileSourceFile(":/shaders/shader.f.glsl");

    if (!_vertexShader->isCompiled())
    {
        qDebug() 
            << "Could not compile vertex shader:\n" 
            << _vertexShader->log();
    }

    if (!_fragmentShader->isCompiled())
    {
        qDebug() 
            << "Could not compile fragment shader:\n" 
            <<  _fragmentShader->log();
    }

}

void Cube::makeGeometry()
{
    const GLfloat vertexData[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 1.0f
    };

    const GLushort elementData[] = {
        0, 1, 2, 3
    };

    _vertexBuffer = QGLBuffer(QGLBuffer::VertexBuffer);
    _elementBuffer = QGLBuffer(QGLBuffer::IndexBuffer);

    _vertexBuffer.create();
    _elementBuffer.create();

    _vertexBuffer.bind();
    _elementBuffer.bind();

    _vertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    _elementBuffer.setUsagePattern(QGLBuffer::StaticDraw);

    _vertexBuffer.allocate((void *)vertexData, sizeof(vertexData));
    _elementBuffer.allocate((void *)elementData, sizeof(elementData));

}
