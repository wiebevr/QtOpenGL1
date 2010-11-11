#include "display_plane.h"
#include <QDebug>

DisplayPlane::DisplayPlane(QObject *parent)
    : Object(parent)
{
    // Timer:
    _timer = new QTimer(this);
    _timer->start(10);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    _positionMatrix.setToIdentity();
    _positionMatrix.translate(0.0f, 0.0f, 1.0f);

}

DisplayPlane::~DisplayPlane()
{
}

void DisplayPlane::timeout()
{
    //_positionMatrix.rotate(1.0f, 1.0f, 0.0f, 0.0f);
}

void DisplayPlane::makeResources()
{
    makeGeometry();
    makeShaders();
}

void DisplayPlane::draw(Camera *camera, QMatrix4x4 position)
{
    _shaderProgram->bind();

    _shaderProgram->setUniformValue(
            "projectionMatrix", 
            camera->getProjectionMatrix());
    _shaderProgram->setUniformValue(
            "modelViewMatrix", 
            camera->getModelViewMatrix() * position * _positionMatrix);

    _vertexBuffer.bind();
    _shaderProgram->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 4);
    _shaderProgram->enableAttributeArray("vertexPosition");

    _elementBuffer.bind();
    glDrawElements(
            GL_TRIANGLE_STRIP,
            4,
            GL_UNSIGNED_SHORT,
            (void *)0);

    _shaderProgram->disableAttributeArray("vertexPosition");

    _shaderProgram->release();

    _vertexBuffer.release();
    _elementBuffer.release();
}

void DisplayPlane::makeShaders()
{
    _shaderProgram = new QGLShaderProgram(this); 

    QGLShader *vertexShader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fragmentShader = new QGLShader(QGLShader::Fragment, this);
    
    vertexShader->compileSourceFile(":/shaders/shader.v.glsl");
    fragmentShader->compileSourceFile(":/shaders/shader.f.glsl");

    if (!vertexShader->isCompiled())
    {
        qDebug() 
            << "Could not compile vertex shader:\n" 
            << vertexShader->log();
    }

    if (!fragmentShader->isCompiled())
    {
        qDebug() 
            << "Could not compile fragment shader:\n" 
            <<  fragmentShader->log();
    }

    _shaderProgram->addShader(fragmentShader);
    _shaderProgram->addShader(vertexShader);

    _shaderProgram->link();
}

void DisplayPlane::makeGeometry()
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

    _vertexBuffer.release();
    _elementBuffer.release();

}
