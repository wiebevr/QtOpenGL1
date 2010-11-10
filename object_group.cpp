#include "object_group.h"

ObjectGroup::ObjectGroup(QObject *parent)
    : Object(parent)
{
    _yRotationAnimation = new QPropertyAnimation(this, "_yRotation");
}

ObjectGroup::~ObjectGroup()
{
}

void ObjectGroup::makeResources()
{
    for(int i = 0; i < _objects.size(); ++i)
    {
        _objects[i].makeResources();
    }
}

void ObjectGroup::addObject(Object *object)
{
    _objects.append(object);
    setFormation(CIRCLE);
}

void ObjectGroup::goToObject(Object *object)
{
    
}

void ObjectGroup::draw(Camera *camera)
{
    for(int i = 0; i < _objects.size(); ++i)
    {
        _objects[i]->draw(camera);
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
                double angle = 360.0 / (double)_objects.size();
                _objects[i]->setPosition(QVector3D(cos(angle), 0.0f, sin(angle)));
            }
            break;

    }
}

