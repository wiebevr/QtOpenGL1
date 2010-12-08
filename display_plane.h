#ifndef DISPLAY_PLANE_H
#define DISPLAY_PLANE_H

#include <QGLBuffer>
#include <QGLShader>
#include <QTimer>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <QVector>
#include <QImage>
#include <QSize>
#include "object.h"

class DisplayPlane
    : public Object
{
    Q_OBJECT

    public:
        DisplayPlane(QObject *parent = 0);
        DisplayPlane(QString texture, QObject *parent = 0);
        ~DisplayPlane();
        void makeResources();
        void draw(Camera *shaderProgram, QMatrix4x4 position = QMatrix4x4());

    private slots:
        void timeout();

    private:
        QTimer *_timer;
        QGLShaderProgram *_shaderProgram;

        QGLBuffer _vertexBuffer;
        QGLBuffer _elementBuffer;
        
        QVector<QVector4D> _vertexData;
        QVector<QVector4D> _normalData;
        QVector<GLfloat> _shininessData;
        QVector<GLfloat> _specularData;

        GLuint _textureId;
        QString _texture;
        QSize _size;

        void makeGeometry();
        void makeShaders();
        void makeTexture();
};

#endif // DISPLAY_PLANE_H
