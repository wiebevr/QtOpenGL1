#include "display_plane.h"
#include <QDebug>
#include <QGLPixelBuffer>

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
    makeGeometry();
    makeShaders();
    makeTexture();
}

void DisplayPlane::draw(Camera *camera, QMatrix4x4 position)
{
    _shaderProgram->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    _shaderProgram->setUniformValue(
            "projectionMatrix", 
            camera->getProjectionMatrix());
    _shaderProgram->setUniformValue(
            "modelViewMatrix", 
            camera->getModelViewMatrix() * position * _positionMatrix);
    _shaderProgram->setUniformValue("texture", 0);

    _shaderProgram->setAttributeArray("vertexPosition", 
            _vertexData.constData());
    _shaderProgram->setAttributeArray("normal", 
            _normalData.constData());
    _shaderProgram->setAttributeArray("shininess", 
            _shininessData.constData(), 1);
    _shaderProgram->setAttributeArray("specular", 
            _specularData.constData(), 1);

    _shaderProgram->enableAttributeArray("vertexPosition");
    _shaderProgram->enableAttributeArray("normal");
    _shaderProgram->enableAttributeArray("shininess");
    _shaderProgram->enableAttributeArray("specular");

    glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexData.size());

    _shaderProgram->disableAttributeArray("vertexPosition");
    _shaderProgram->disableAttributeArray("normal");
    _shaderProgram->disableAttributeArray("shininess");
    _shaderProgram->disableAttributeArray("specular");


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
    QImage image(_texture);
    QGLPixelBuffer pixelBuffer(image.size());

    _textureId = pixelBuffer.bindTexture(image);
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
