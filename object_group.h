#ifndef OBJECT_GROUP_H
#define OBJECT_GROUP_H
#include <QVector>
#include <QObject>
#include <QVector3D>
#include <QPropertyAnimation>

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
