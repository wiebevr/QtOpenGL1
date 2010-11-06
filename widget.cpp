#include "widget.h"
#include <QMatrix4x4>

Widget::Widget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    _cube = new Cube(this);
    _mesh = new Mesh(this);    
    _widgetPlane = new WidgetPlane(this);

    _camera = new Camera(45.0f, (double)width() / (double)height(),
            1.0f, 15.0f, this);
    _camera->setRotationPoint(QVector3D(0.0f, 0.0f, 5.0f));

    _drawTimer = new QTimer(this);
    _drawTimer->start(10);
    connect(_drawTimer, SIGNAL(timeout()), this, SLOT(updateGL()));

    isDragging = false;

}

Widget::~Widget()
{    
}

void Widget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_ARRAY);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    _cube->makeResources();
    _mesh->makeResources();
    _widgetPlane->makeResources();
    
}

void Widget::paintGL()
{
    qglClearColor(Qt::gray);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    //_mesh->draw(_camera);
    _widgetPlane->draw(_camera);
    //_cube->draw(_camera);
}

void Widget::resizeGL(int width, int height)
{
    qDebug() << "Width: " << width;
    qDebug() << "Height: " << height;
    _camera->resize(width, height);
    glViewport(0, 0, width, height);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPointF position(
                event->posF().x() / this->size().width(),
                event->posF().y() / this->size().height());
        if (isDragging)
        {
            QPointF position(
                    event->posF().x() / this->size().width(),
                    event->posF().y() / this->size().height());
            _camera->rotate(
                    (position.x() - _lastMousePosition.x()) * 100.0f,
                    QVector3D(0.0f, 1.0f, 0.0f));
            _camera->rotate(
                    (position.y() - _lastMousePosition.y()) * 100.0f,
                    QVector3D(1.0f, 0.0f, 0.0f));
        }
        _lastMousePosition = position;
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    event->ignore();
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        _lastMousePosition = QPointF(
                event->posF().x() / this->size().width(),
                event->posF().y() / this->size().height());

        isDragging = true;
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) == 0)
    {
        isDragging = false;
    }
}
