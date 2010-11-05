#ifndef WIDGET_H
#define WIDGET_H

#include "cube.h"
#include "camera.h"

#include <QGLWidget>
#include <QGLFormat>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QMouseEvent>

class Widget : public QGLWidget
{
    Q_OBJECT
    
    public:
        Widget(QWidget *parent = 0);
        ~Widget();
    
    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);

        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);


    private:
        Cube *_cube;
        QGLShaderProgram *_shaderProgram;
        QTimer *_drawTimer;
#if 0        
        QMatrix4x4 _projectionMatrix;
        QMatrix4x4 _modelViewMatrix;
        QVector3D _positionVector;
        QMatrix4x4 _rotationMatrix;
#endif
        Camera *_camera; 

        QPointF _lastMousePosition;
        bool isDragging;
};

#endif // WIDGET_H
