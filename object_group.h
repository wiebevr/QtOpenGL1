#ifndef OBJECT_GROUP_H
#define OBJECT_GROUP_H
#include "object.h"
#include "camera.h"
#include <QVector>
#include <QObject>
#include <QVector3D>
#include <QPropertyAnimation>
#include <math.h>

class ObjectGroup
    : public Object
{
    Q_OBJECT

    public:
        ObjectGroup(QObject *parent = 0);
        ~ObjectGroup();
        void addObject(Object *object);
        bool removeObject(Object *object);
        void goToObject(Object *object);
        void setFormation(int formation);
        void draw(Camera *camera);
        void makeResources();
    enum
    {
        CIRCLE
    };

    private:
        QVector<Object *> _objects;
        double _rotation;
        QPropertyAnimation *_yRotationAnimation;
};

#endif //OBJECT_GROUP_H
