#ifndef MESH_H
#define MESH_H

#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <QGLShaderProgram>
#include <QVector>
#include <QVector3D>

#include "object.h"

class Mesh
    : public Object
{
    Q_OBJECT

    public:
        Mesh(QObject *parent = 0);
        ~Mesh();
        void makeResources();
        void draw(Camera *camera);

    private:
        void makeGeometry();
        void makeShaders();

        QVector<QVector3D> _vertices;
        QGLShaderProgram *_shaderProgram;

};
#endif // MESH_H
