#ifndef OBJECT_GROUP_H
#define OBJECT_GROUP_H
#include "object.h"
#include "camera.h"
#include <QVector>
#include <QObject>
#include <QVector3D>
#include <QPropertyAnimation>
#include <QMatrix4x4>
#include <math.h>

class ObjectGroup
    : public Object
{
    Q_OBJECT

    public:
        ObjectGroup(QObject *parent = 0);
        virtual ~ObjectGroup();
        void addObject(Object *object);
        void removeObject(Object *object);
        void removeObject(int object);
        void setFormation(int formation);
        void draw(Camera *camera, QMatrix4x4 position = QMatrix4x4());
        void makeResources();

        void goToObject(Object *object);
        void goToObject(int object);
        void goToNearest();
        void goLeft();
        void goRight();

        enum
        {
            CIRCLE,
            GRID
        };

    private:
        QVector<Object *> _objects;
        double _rotation;
        int _currentObject;
        QPropertyAnimation *_rotationAnimation;
};

#endif //OBJECT_GROUP_H
