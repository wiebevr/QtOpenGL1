#include "mesh.h"
#include <QFile>

Mesh::Mesh(QObject *parent)
    : Object(parent)
{
    _meshFilename = QString("media/monkey.obj");
    _positionMatrix.setToIdentity();
    _positionMatrix.translate(0.0f, 0.0f, -1.5f);
}

Mesh::Mesh(QString meshFilename, QObject *parent)
    : Object(parent)
{
    _meshFilename = meshFilename;
    _positionMatrix.setToIdentity();
    _positionMatrix.translate(0.0f, 0.0f, -1.5f);
}

Mesh::~Mesh()
{
}

void Mesh::makeResources()
{
    makeGeometry();
    makeShaders();
}

void Mesh::draw(Camera *camera, QMatrix4x4 position)
{
    _shaderProgram->bind();

    _shaderProgram->setUniformValue(
            "projectionMatrix", 
            camera->getProjectionMatrix());
    _shaderProgram->setUniformValue(
            "modelViewMatrix", 
            camera->getModelViewMatrix() * position * _positionMatrix);

    _shaderProgram->setAttributeArray("vertexPosition", 
            _vertexData.constData());
    _shaderProgram->setAttributeArray("normal", 
            _normalData.constData());
    _shaderProgram->setAttributeArray("shininess", 
            _shininessData.constData(), 1);
    _shaderProgram->setAttributeArray("specular", GL_UNSIGNED_BYTE,
            (void *)_specularData.constData(), 4);

    _shaderProgram->enableAttributeArray("vertexPosition");
    _shaderProgram->enableAttributeArray("normal");
    _shaderProgram->enableAttributeArray("shininess");
    _shaderProgram->enableAttributeArray("specular");

    glDrawArrays(GL_TRIANGLES, 0, _vertexData.size());

    _shaderProgram->disableAttributeArray("vertexPosition");
    _shaderProgram->disableAttributeArray("normal");
    _shaderProgram->disableAttributeArray("shininess");
    _shaderProgram->disableAttributeArray("specular");
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
    const aiScene *scene = importer.ReadFile(_meshFilename.toStdString(),
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            //aiProcess_JoinIdenticalVertices |
            aiProcess_SortByPType);
    const aiMesh *mesh;
    int numberOfVertices;
    GLubyte specularData[] = {0, 0, 0, 0};
    aiVector3D *vertices;
    aiVector3D *normals;

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
    normals = mesh->mNormals;

    for ( int i = 0; i < numberOfVertices; ++i )
    {
        _vertexData.append(
                QVector4D(vertices[i].x, vertices[i].y, vertices[i].z, 1.0f));
        _normalData.append(
                QVector4D(normals[i].x, normals[i].y, normals[i].z, 0.0f));
        _shininessData.append(0.8f);
        _specularData.append(specularData);
    }
    qDebug() << _vertexData;

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
