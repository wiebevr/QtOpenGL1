#include "widget.h"
#include "picture_folder_group.h"

#include <QMatrix4x4>
#include <QString>

#define NUMBER_OF_OBJECTS 5

Widget::Widget(QString folder, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DepthBuffer), parent)
{
    _objectGroup = new PictureFolderGroup(folder, this);
    setWindowState(Qt::WindowFullScreen);

    _camera = new Camera(60.0f, (double)width() / (double)height(),
            1.0f, 200.0f, this);
    _camera->setRotationPoint(QVector3D(0.0f, 0.0f, 9.0f));

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
    glEnable(GL_TEXTURE_2D);

    _objectGroup->makeResources();
    
}

void Widget::paintGL()
{
    qglClearColor(Qt::black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _objectGroup->draw(_camera);
   
    //_mesh->draw(_camera);
    //_widgetPlane->draw(_camera);
    //_displayPlane->draw(_camera);
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
            _objectGroup->setRotation(_objectGroup->getRotation() + 
                    QVector3D((position.y() - _lastMousePosition.y()) * 100.0f,
                        (position.x() - _lastMousePosition.x()) * 100.0f, 0.0f));
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
    switch(event->key())
    {
        case Qt::Key_Right:
            _objectGroup->goRight();
            event->accept();
            break;

        case Qt::Key_Left:
            _objectGroup->goLeft();
            event->accept();
            break;

        default:
            event->ignore();
    }
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
        _objectGroup->goToNearest();
    }
}
