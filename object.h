#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QGLBuffer>
#include <QGLShader>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector>
#include <QTimer>

class Object
    : public QObject
{
    Q_OBJECT

    public:
        Object(QObject *parent = 0);
        virtual ~Object();
        virtual QGLShader *getVertexShader() const;
        virtual QGLShader *getFragmentShader() const;
        virtual QGLBuffer getVertexBuffer() const;
        virtual QGLBuffer getElementBuffer() const;
        virtual QMatrix4x4 getPositionMatrix() const;
        virtual void setPositionMatrix(QMatrix4x4 positionMatrix);
        virtual void makeResources() = 0;

    protected:
        QGLBuffer _vertexBuffer;
        QGLBuffer _elementBuffer;

        QGLShader *_vertexShader;
        QGLShader *_fragmentShader;

        QMatrix4x4 _positionMatrix;
};

#endif // OBJECT_H
