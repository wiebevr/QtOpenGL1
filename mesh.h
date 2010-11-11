#ifndef MESH_H
#define MESH_H

#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <QGLShaderProgram>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>

#include "object.h"

class Mesh
    : public Object
{
    Q_OBJECT

    public:
        Mesh(QObject *parent = 0);
        ~Mesh();
        void makeResources();
        void draw(Camera *camera, QMatrix4x4 position = QMatrix4x4());

    private:
        void makeGeometry();
        void makeShaders();

        QVector<QVector3D> _vertices;
        QGLShaderProgram *_shaderProgram;

};
#endif // MESH_H
