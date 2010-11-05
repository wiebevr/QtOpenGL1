#ifndef CUBE_H
#define CUBE_H

#include <QObject>
#include <QGLBuffer>
#include <QGLShader>
#include <QMatrix4x4>
#include <QVector4D>
#include <QVector>
#include <QTimer>

class Cube
    : public QObject
{
    Q_OBJECT

    public:
        Cube(QObject *parent = 0);
        ~Cube();
        QGLShader *getVertexShader() const;
        QGLShader *getFragmentShader() const;
        const QVector<QVector3D> &getVertexData() const;
        QGLBuffer getVertexBuffer() const;
        QGLBuffer getElementBuffer() const;
        QMatrix4x4 getWorldMatrix() const;
        void setWorldMatrix(QMatrix4x4 worldMatrix);
        void makeResources();

    protected:
        void makeGeometry();
        void makeShaders();
    
    protected slots:
        void timeout();
    

    private:
        QTimer *_timer;

        QGLBuffer _vertexBuffer;
        QGLBuffer _elementBuffer;

        QGLShader *_vertexShader;
        QGLShader *_fragmentShader;

        QMatrix4x4 _worldMatrix;

        QVector<QVector3D> _vertexData;
};

#endif // CUBE_H
