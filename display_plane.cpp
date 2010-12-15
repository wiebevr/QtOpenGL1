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
}

DisplayPlane::DisplayPlane(QString texture, QObject *parent)
    : Object(parent)
{
    _texture = texture;
    _size = QImage(texture).size();

    // Timer:
    _timer = new QTimer(this);
    _timer->start(10);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    _positionMatrix.setToIdentity();
    qDebug() << _size;
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
    QGLConext::currentContext()->makeCurrent();
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

    _shaderProgram->setAttributeArray("vertexPosition", 
            _vertexData.constData());

    _shaderProgram->enableAttributeArray("vertexPosition");

    glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexData.size());

    _shaderProgram->disableAttributeArray("vertexPosition");

#if 0
    _vertexBuffer.bind();
    _shaderProgram->setAttributeValue("normal", QVector4D(0.0f, 0.0f, -1.0f, 1.0f));
    //_shaderProgram->setAttributeValue("shininess", );
    _shaderProgram->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 4);
    _shaderProgram->enableAttributeArray("normal");
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
#endif
    _shaderProgram->release();
}

void DisplayPlane::makeShaders()
{
    _shaderProgram = new QGLShaderProgram(this); 

    QGLShader *vertexShader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fragmentShader = new QGLShader(QGLShader::Fragment, this);

    qDebug() << "Sharder object made";
    qDebug() << QGLShaderProgram::hasOpenGLShaderPrograms();
    
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

void DisplayPlane::makeTexture()
{
    QImage image(QGLWidget::convertToGLFormat(QImage(_texture)));

    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0,
            GL_RGBA, image.width(), image.height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)image.constBits());
    setScale(QVector3D(
            (qreal)image.size().width() / (qreal)image.size().height(),
            1.0, 1.0));
}

void DisplayPlane::makeGeometry()
{
#if 0
    const GLfloat vertexData[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 1.0f,
         //
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
#endif
    _vertexData.append(QVector4D(-1.0f, -1.0f, 0.0f, 1.0f));
    _vertexData.append(QVector4D( 1.0f, -1.0f, 0.0f, 1.0f));
    _vertexData.append(QVector4D(-1.0f,  1.0f, 0.0f, 1.0f));
    _vertexData.append(QVector4D( 1.0f,  1.0f, 0.0f, 1.0f));

    _normalData.append(QVector4D(0.0f, 0.0f, 1.0f, 0.0f));
    _normalData.append(QVector4D(0.0f, 0.0f, 1.0f, 0.0f));
    _normalData.append(QVector4D(0.0f, 0.0f, 1.0f, 0.0f));
    _normalData.append(QVector4D(0.0f, 0.0f, 1.0f, 0.0f));

    _shininessData.append(0.0f);
    _shininessData.append(0.0f);
    _shininessData.append(0.0f);
    _shininessData.append(0.0f);

    _specularData.append(0.0f);
    _specularData.append(0.0f);
    _specularData.append(0.0f);
    _specularData.append(0.0f);
}
