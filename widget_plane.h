#ifndef WIDGET_PLANE_H
#define WIDGET_PLANE_H

#include <QGLBuffer>
#include <QGLShader>
#include <QTimer>
#include <QGLShaderProgram>
#include <QWidget>
#include <QGLFramebufferObject>
#include <QMatrix4x4>

#include "object.h"

class WidgetPlane
    : public Object
{
    Q_OBJECT

    public:
        WidgetPlane(QObject *parent = 0);
        ~WidgetPlane();
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

        QGLFramebufferObject *_framebufferObject;
        QWidget *_widget;
};

#endif // WIDGET_PLANE_H
