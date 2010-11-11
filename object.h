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
    Q_PROPERTY(QVector3D _position READ getPosition WRITE setPosition) 
    Q_PROPERTY(QVector3D _rotation READ getRotation WRITE setRotation) 
    Q_PROPERTY(QVector3D _scale READ getScale WRITE setScale) 
    Q_PROPERTY(double _zRotation READ getZRotation WRITE setZRotation) 
    Q_PROPERTY(double _yRotation READ getYRotation WRITE setYRotation) 
    Q_PROPERTY(double _xRotation READ getXRotation WRITE setXRotation) 

    public:
        Object(QObject *parent = 0);
        virtual ~Object();

        virtual QMatrix4x4 getPositionMatrix() const;
        virtual void setPositionMatrix(QMatrix4x4 positionMatrix);

        virtual void makeResources() = 0;
        virtual void draw(Camera *camera, QMatrix4x4 position = QMatrix4x4()) = 0;
        QVector3D getPosition() const;
        void setPosition(QVector3D postion);
        QVector3D getRotation() const;
        QVector3D getScale() const;
        void setScale(QVector3D scale);

        void setRotation(QVector3D rotation);
        double getYRotation() const;
        void setYRotation(double yRotation);
        double getXRotation() const;
        void setXRotation(double xRotation);
        double getZRotation() const;
        void setZRotation(double zRotation);


    protected:
        QMatrix4x4 _positionMatrix;

    private:
        void updatePositionMatrix();
        QVector3D _position;
        QVector3D _rotation;
        QVector3D _scale;
};

#endif // OBJECT_H
