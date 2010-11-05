#include "mesh.h"

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

void Mesh::makeShaders()
{
    _vertexShader = new QGLShader(QGLShader::Vertex, this);
    _fragmentShader = new QGLShader(QGLShader::Fragment, this);
    
    _vertexShader->compileSourceFile(":/shaders/shader.v.glsl");
    _fragmentShader->compileSourceFile(":/shaders/shader.f.glsl");

    if (!_vertexShader->isCompiled())
    {
        qDebug() 
            << "Could not compile vertex shader:\n" 
            << _vertexShader->log();
    }

    if (!_fragmentShader->isCompiled())
    {
        qDebug() 
            << "Could not compile fragment shader:\n" 
            <<  _fragmentShader->log();
    }
}

void Mesh::makeGeometry()
{
    Assimp::Importer importer;
    i//const aiScene *scene = importer.ReadFile("filename"


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
}
