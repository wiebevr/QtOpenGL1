#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>
#include "camera.h"

class Object
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D _position READ getPosition WIRTE setPosition) 
    Q_PROPERTY(double _yRotation READ getYRotation WIRTE setYRotation) 

    public:
        Object(QObject *parent = 0);
        virtual ~Object();

        virtual QMatrix4x4 getPositionMatrix() const;
        virtual void setPositionMatrix(QMatrix4x4 positionMatrix);

        virtual void makeResources() = 0;
        virtual void draw(Camera *camera) = 0;
        QVector3D getPosition() const;
        void setPosition(QVector3D postion);
        double getYRotation() const;
        void setYRotation(double yRotation);

    protected:
        QMatrix4x4 _positionMatrix;
};

#endif // OBJECT_H
