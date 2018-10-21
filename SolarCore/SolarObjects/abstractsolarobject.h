#ifndef ABSTRACTSOLAROBJECT_H
#define ABSTRACTSOLAROBJECT_H

#include <QObject>
#include "solarsystemcore.h"
#include <memory>

namespace SolarSystem
{
    //simple presentation of math solar object
    class AbstractSolarObject : public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractSolarObject(QObject* parent = nullptr);
        virtual ~AbstractSolarObject();

        //getters + setters
        float radius() const;
        void setRadius(float radius);

        float tilt() const;
        void setTilt(float tilt);

        float roll() const;
        void setRoll(float roll);

        float x() const;
        void setX(float x);

        float y() const;
        void setY(float y);

        float z() const;
        void setZ(float z);

        //only getters
        float N1() const;
        float N2() const;
        float i1() const;
        float i2() const;
        float w1() const;
        float w2() const;
        float a1() const;
        float a2() const;
        float e1() const;
        float e2() const;
        float M1() const;
        float M2() const;
        float period() const;
        SolarObjects centerOfOrbit() const;
        SolarObjects object() const;

    protected:

        //main data
        float m_Radius = 0;
        float m_Tilt = 0;
        float m_N1 = 0;
        float m_N2 = 0;
        float m_I1 = 0;
        float m_I2 = 0;
        float m_W1 = 0;
        float m_W2 = 0;
        float m_A1 = 0;
        float m_A2 = 0;
        float m_E1 = 0;
        float m_E2 = 0;
        float m_M1 = 0;
        float m_M2 = 0;
        float m_Period = 0;
        float m_X = 0;
        float m_Y = 0;
        float m_Z = 0;
        float m_Roll = 0;
        SolarObjects m_CenterOfOrbit;
        SolarObjects m_ObjectType;

        virtual void initialize() = 0;
    };

    //solar objects type
    using SolarObjectPtr = std::shared_ptr < AbstractSolarObject >;
    using SolarObjectsArray = std::vector < SolarObjectPtr >;
}

#endif // ABSTRACTSOLAROBJECT_H
