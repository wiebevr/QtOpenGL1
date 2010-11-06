#include "widget_plane.h"
#include <QDebug>
#include <QGLFramebufferObjectFormat>
#include <QLineEdit>
#include <QGLContext>
#include <QGLFormat>

WidgetPlane::WidgetPlane(QObject *parent)
    : Object(parent)
{
    // Timer:
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timeout()));
    _widget = new QLineEdit(QString("Dit is een test"));
    _timer->start(10);
    _widget->resize(100, 100);
    //_widget->show();
}

WidgetPlane::~WidgetPlane()
{
}

void WidgetPlane::timeout()
{
}

void WidgetPlane::makeResources()
{
    QGLFramebufferObjectFormat framebufferFormat;
    _framebufferObject = new QGLFramebufferObject(_widget->size(), 
            framebufferFormat);

    makeGeometry();
    makeShaders();
    _widget->render(_framebufferObject); 
}

void WidgetPlane::draw(Camera *camera)
{
    _shaderProgram->bind();

    _shaderProgram->setUniformValue(
            "projectionMatrix", 
            camera->getProjectionMatrix());
    _shaderProgram->setUniformValue(
            "modelViewMatrix", 
            camera->getModelViewMatrix());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _framebufferObject->handle());
    _shaderProgram->setUniformValue("texture", 0);

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
    //_widget->render(_framebufferObject); 
}

void WidgetPlane::makeShaders()
{
    _shaderProgram = new QGLShaderProgram(this); 

    QGLShader *vertexShader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fragmentShader = new QGLShader(QGLShader::Fragment, this);
    
    vertexShader->compileSourceFile(":/shaders/widget_plane.v.glsl");
    fragmentShader->compileSourceFile(":/shaders/widget_plane.f.glsl");

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

void WidgetPlane::makeGeometry()
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
