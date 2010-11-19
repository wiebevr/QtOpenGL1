#ifndef MESH_H
#define MESH_H

#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <QGLShaderProgram>
#include <QVector>
#include <QString>
#include <QVector3D>
#include <QMatrix4x4>

#include "object.h"

class Mesh
    : public Object
{
    Q_OBJECT

    public:
        Mesh(QObject *parent = 0);
        Mesh(QString meshFilename, QObject *parent = 0);
        ~Mesh();
        void makeResources();
        void draw(Camera *camera, QMatrix4x4 position = QMatrix4x4());

    private:
        void makeGeometry();
        void makeShaders();

        QVector<QVector4D> _vertexData;
        QVector<QVector4D> _normalData;
        QVector<GLfloat> _shininessData;
        QVector<GLubyte *> _specularData;

        QGLShaderProgram *_shaderProgram;
        QString _meshFilename;

};
#endif // MESH_H
