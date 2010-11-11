#ifndef DISPLAY_PLANE_H
#define DISPLAY_PLANE_H

#include <QGLBuffer>
#include <QGLShader>
#include <QTimer>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include "object.h"

class DisplayPlane
    : public Object
{
    Q_OBJECT

    public:
        DisplayPlane(QObject *parent = 0);
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

        void makeGeometry();
        void makeShaders();
};

#endif // DISPLAY_PLANE_H