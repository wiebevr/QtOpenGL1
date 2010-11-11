#include "object_group.h"
#include <QEasingCurve>
#define PI 3.1415926535897

ObjectGroup::ObjectGroup(QObject *parent)
    : Object(parent)
{
    _rotationAnimation = new QPropertyAnimation(this, "_rotation", this);
    _rotationAnimation->setEasingCurve(QEasingCurve::OutBack);
    _rotationAnimation->setDuration(1000);
    _currentObject = 0;
}

ObjectGroup::~ObjectGroup()
{
}

void ObjectGroup::makeResources()
{
    for(int i = 0; i < _objects.size(); ++i)
    {
        _objects[i]->makeResources();
    }
}

void ObjectGroup::addObject(Object *object)
{
    _objects.append(object);
    setFormation(CIRCLE);
}

void ObjectGroup::goToNearest()
{
    if (_rotationAnimation->state() == QAbstractAnimation::Stopped)
    {
        int index;
        //setYRotation((360.0 / _objects.size()) * _currentObject);
        index = qRound(((qreal)(getYRotation() * (qreal)_objects.size()) / 
                    360.0));
        goToObject(index);

    }
}

void ObjectGroup::goToObject(Object *object)
{
    int index = _objects.indexOf(object);
    if (index >= 0)
    {
        goToObject(index);
    }
}
void ObjectGroup::goToObject(int object)
{
    if (_rotationAnimation->state() == QAbstractAnimation::Stopped) 
    {
        QVector3D endAngle = 
            QVector3D(0.0f, (360.0 / _objects.size()) * object, 0.0f);

        if (getYRotation() >= 360.0)
            setYRotation(getYRotation() - 360.0);
        if (getYRotation() < 0.0)
            setYRotation(getYRotation() + 360.0);

        qDebug() << "Gooing from" << getYRotation() << "to" << endAngle.y();
        qDebug() << object << getYRotation();

        //setYRotation((360.0 / _objects.size()) * _currentObject);

        _rotationAnimation->setStartValue(getRotation());    
        _rotationAnimation->setEndValue(endAngle);
        _rotationAnimation->start();
        _currentObject = object;


        if (_currentObject >= _objects.size())
            _currentObject -= _objects.size();

        if (_currentObject < 0)
            _currentObject += _objects.size();
    }
}

void ObjectGroup::goLeft()
{
    if (_rotationAnimation->state() == QAbstractAnimation::Stopped)
        goToObject(_currentObject + 1);
}

void ObjectGroup::goRight()
{
    if (_rotationAnimation->state() == QAbstractAnimation::Stopped)
        goToObject(_currentObject - 1);
}

void ObjectGroup::draw(Camera *camera, QMatrix4x4 position)
{
    for(int i = 0; i < _objects.size(); ++i)
    {
        _objects[i]->draw(camera, position * _positionMatrix);
    }
}

void ObjectGroup::setFormation(int formation)
{
    switch(formation)
    {
        case CIRCLE:
        default:
            for (int i = 0; i < _objects.size(); ++i)
            {
                _objects[i]->setPosition(QVector3D(0.0f, 0.0f, 1.0f) * 2.5);
                _objects[i]->setYRotation((360.0 / _objects.size()) * i);
            }
            break;
        case GRID:
            int size = sqrt(_objects.size()) + 1;
            double scale = (1.7 / (double) size);
            for (int i = 0; i < _objects.size(); ++i)
            {
                _objects[i]->setScale(QVector3D(scale, scale, 1.0));
                _objects[i]->setPosition(QVector3D(
                    ((double)(i % size) * 2.2 * scale),// - 0.5 / scale,
                    -((double)(i / size) * 2.2 * scale),// + 0.5 / scale, 
                    0.0f));
            }
            break;

    }
}

