#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QMatrix4x4>
#include "camera.h"

class Object
    : public QObject
{
    Q_OBJECT

    public:
        Object(QObject *parent = 0);
        virtual ~Object();

        virtual QMatrix4x4 getPositionMatrix() const;
        virtual void setPositionMatrix(QMatrix4x4 positionMatrix);

        virtual void makeResources() = 0;
        virtual void draw(Camera *camera) = 0;

    protected:
        QMatrix4x4 _positionMatrix;
};

#endif // OBJECT_H
