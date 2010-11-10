#include "object_group.h"

ObjectGroup::ObjectGroup(QObject *parent)
    : QObject(parent)
{
    _yRotationAnimation = new QPropertyAnimation(this, "_yRotation");
}

ObjectGroup::~ObjectGroup()
{
}

void ObjectGroup::addObject(Object *object)
{
    _objects.append(object);
    void setFormation(CIRCLE);
}

void ObjectGroup::goToObject(Object *object)
{
    
}

void ObjectGroup::setFormation(int formation)
{
    switch(foramtion)
    {
        case CIRCLE:
        default:

            break;

    }
}

