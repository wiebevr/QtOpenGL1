#ifndef WIDGET_H
#define WIDGET_H

#include "cube.h"
#include "camera.h"
#include "display_plane.h"
#include "object_group.h"

#include <QGLWidget>
#include <QGLFormat>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QGraphicsView>

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
        DisplayPlane *_displayPlane;
        ObjectGroup *_objectGroup;

        QTimer *_drawTimer;
        Camera *_camera; 

        QPointF _lastMousePosition;
        bool isDragging;
};

#endif // WIDGET_H
