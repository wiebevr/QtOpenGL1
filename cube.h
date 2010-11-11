#ifndef CUBE_H
#define CUBE_H

#include <QGLBuffer>
#include <QGLShader>
#include <QTimer>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include "object.h"

class Cube
    : public Object
{
    Q_OBJECT

    public:
        Cube(QObject *parent = 0);
        ~Cube();
        void makeResources();
        void draw(Camera *camera, QMatrix4x4 position = QMatrix4x4());

    private slots:
        void timeout();

    private:
        QTimer *_timer;
        QGLShaderProgram *_shaderProgram;

        QGLBuffer _vertexBuffer;
        QGLBuffer _elementBuffer;

        void makeGeometry();
        void makeShaders();
};

#endif // CUBE_H
