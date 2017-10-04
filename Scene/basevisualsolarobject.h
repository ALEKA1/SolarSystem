#ifndef BASEVISUALSOLAROBJECT_H
#define BASEVISUALSOLAROBJECT_H

#include "Scene/visualsolarobject.h"

namespace SolarSystem
{
    //this class represets a simple visual object with transform and mesh
    class BaseVisualSolarObject : public VisualSolarObject
    {
        Q_OBJECT

    public:
        BaseVisualSolarObject(Qt3DCore::QNode* parent = nullptr);

    protected:
        virtual void update(float deltaTime) = 0;

    public:
        virtual Qt3DRender::QObjectPicker& picker() const = 0;

        //realize base visual methods
        virtual Qt3DCore::QTransform& transform() const override final;
        virtual Qt3DRender::QMesh& mesh() const override final;

        //setters/getters
        virtual SolarObjects solarType() const override final;
        virtual void setSolarType(SolarObjects type) override final;

        virtual double r() const override final;
        virtual void setR(double r) override final;

        virtual double x() const override final;
        virtual void setX(double x) override final;

        virtual double y() const override final;
        virtual void setY(double y) override final;

        virtual double z() const override final;
        virtual void setZ(double z) override final;

        virtual double roll() const override final;
        virtual void setRoll(double roll) override final;

        virtual double tilt() const override final;
        virtual void setTilt(double tilt) override final;

    private:

        //Qt3D components
        Qt3DCore::QTransform* _transform;
        Qt3DRender::QMesh* _mesh;

    protected:

        //main data
        SolarObjects _solarType;
        double _r = 0;
        double _x = 0;
        double _y = 0;
        double _z = 0;
        double _roll = 0;
        double _tilt = 0;
    };
}

#endif // BASEVISUALSOLAROBJECT_H
