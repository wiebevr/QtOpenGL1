#ifndef MESH_H
#define MESH_H

//#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <iostream>
#include <string>
#include "object.h"
class Mesh
    : public Object
{
    Q_OBJECT

    public:
        Mesh(QObject *parent = 0);
        ~Mesh();
        void makeResources();

    private:
        void makeGeometry();
        void makeShaders();

};
#endif // MESH_H
