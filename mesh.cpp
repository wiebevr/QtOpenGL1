#include "mesh.h"
#include <QFile>

Mesh::Mesh(QObject *parent)
    : Object(parent)
{
}

Mesh::~Mesh()
{
}

void Mesh::makeResources()
{
    makeGeometry();
    makeShaders();
}

void Mesh::draw(Camera *camera)
{
    _shaderProgram->bind();
    
    _shaderProgram->setUniformValue(
            "projectionMatrix", 
            camera->getProjectionMatrix());
    _shaderProgram->setUniformValue(
            "modelViewMatrix", 
            camera->getModelViewMatrix());

    _shaderProgram->enableAttributeArray("vertexPosition");
    _shaderProgram->setAttributeArray("vertexPosition", _vertices.constData());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertices.size());
    
    _shaderProgram->disableAttributeArray("vertexPosition");
    _shaderProgram->release();
}

void Mesh::makeShaders()
{
    _shaderProgram = new QGLShaderProgram(this);

    QGLShader *vertexShader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fragmentShader = new QGLShader(QGLShader::Fragment, this);
    
    vertexShader->compileSourceFile(":/shaders/shader.v.glsl");
    fragmentShader->compileSourceFile(":/shaders/shader.f.glsl");

    if (!vertexShader->isCompiled())
    {
        qDebug() 
            << "Could not compile vertex shader:\n" 
            << vertexShader->log();
    }

    if (!fragmentShader->isCompiled())
    {
        qDebug() 
            << "Could not compile fragment shader:\n" 
            << fragmentShader->log();
    }
    _shaderProgram->addShader(fragmentShader);
    _shaderProgram->addShader(vertexShader);

    _shaderProgram->link();
}

void Mesh::makeGeometry()
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("media/simple_cube.obj",
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType);
    const aiMesh *mesh;
    int numberOfVertices;
    aiVector3D *vertices;

    if ( !scene )
    {
        qDebug() << "WARNING: Geometry import failed.";
        return;
    }
    if ( !scene->HasMeshes() || scene->mNumMeshes < 1 )
    {
        qDebug() << "WARNING: Can't load geometry: \
            Imported file doesn't have any meshes.";
        return;
    }
    if ( scene->mNumMeshes > 1)
    {
        qDebug() << "Imported file has multiple meshes, using first one.";
    }
    mesh = *(scene->mMeshes);
    numberOfVertices = mesh->mNumVertices;
    vertices = mesh->mVertices;

    for ( int i = 0; i < numberOfVertices; ++i )
    {
        _vertices.append(
                QVector3D(vertices[i].x, vertices[i].y, vertices[i].z));
    }
    qDebug() << _vertices;

#if 0
    _vertexBuffer = QGLBuffer(QGLBuffer::VertexBuffer);
    _elementBuffer = QGLBuffer(QGLBuffer::IndexBuffer);

    _vertexBuffer.create();
    _elementBuffer.create();

    _vertexBuffer.bind();
    _elementBuffer.bind();

    _vertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    _elementBuffer.setUsagePattern(QGLBuffer::StaticDraw);

    _vertexBuffer.allocate((void *)vertexData, sizeof(vertexData));
    _elementBuffer.allocate((void *)elementData, sizeof(elementData));
#endif
}
