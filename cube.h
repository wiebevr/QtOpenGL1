#ifndef CUBE_H
#define CUBE_H

#include <QObject>
#include <QGLBuffer>
#include <QGLShader>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector>
#include <QTimer>
#include "object.h"

class Cube
    : public Object
{
    Q_OBJECT

    public:
        Cube(QObject *parent = 0);
        ~Cube();
        void makeResources();

    private slots:
        void timeout();

    private:
        QTimer *_timer;

        void makeGeometry();
        void makeShaders();

};

#endif // CUBE_H
