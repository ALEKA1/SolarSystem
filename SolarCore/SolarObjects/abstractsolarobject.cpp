#include "abstractsolarobject.h"

SolarSystem::AbstractSolarObject::AbstractSolarObject(QObject* parent):
    QObject(parent)
{
}

SolarSystem::AbstractSolarObject::~AbstractSolarObject()
{
}

float SolarSystem::AbstractSolarObject::radius() const
{
    return m_Radius;
}

void SolarSystem::AbstractSolarObject::setRadius(float radius)
{
    m_Radius = radius;
}

float SolarSystem::AbstractSolarObject::tilt() const
{
    return m_Tilt;
}

void SolarSystem::AbstractSolarObject::setTilt(float tilt)
{
    m_Tilt = tilt;
}

float SolarSystem::AbstractSolarObject::roll() const
{
    return m_Roll;
}

void SolarSystem::AbstractSolarObject::setRoll(float roll)
{
    m_Roll = roll;
}

float SolarSystem::AbstractSolarObject::x() const
{
    return m_X;
}

void SolarSystem::AbstractSolarObject::setX(float x)
{
    m_X = x;
}

float SolarSystem::AbstractSolarObject::y() const
{
    return m_Y;
}

void SolarSystem::AbstractSolarObject::setY(float y)
{
    m_Y = y;
}

float SolarSystem::AbstractSolarObject::z() const
{
    return m_Z;
}

void SolarSystem::AbstractSolarObject::setZ(float z)
{
    m_Z = z;
}

float SolarSystem::AbstractSolarObject::N1() const
{
    return m_N1;
}

float SolarSystem::AbstractSolarObject::N2() const
{
    return m_N2;
}

float SolarSystem::AbstractSolarObject::i1() const
{
    return m_I1;
}

float SolarSystem::AbstractSolarObject::i2() const
{
    return m_I2;
}

float SolarSystem::AbstractSolarObject::w1() const
{
    return m_W1;
}

float SolarSystem::AbstractSolarObject::w2() const
{
    return m_W2;
}

float SolarSystem::AbstractSolarObject::a1() const
{
    return m_A1;
}

float SolarSystem::AbstractSolarObject::a2() const
{
    return m_A2;
}

float SolarSystem::AbstractSolarObject::e1() const
{
    return m_E1;
}

float SolarSystem::AbstractSolarObject::e2() const
{
    return m_E2;
}

float SolarSystem::AbstractSolarObject::M1() const
{
    return m_M1;
}

float SolarSystem::AbstractSolarObject::M2() const
{
    return m_M2;
}

float SolarSystem::AbstractSolarObject::period() const
{
    return m_Period;
}

SolarSystem::SolarObjects SolarSystem::AbstractSolarObject::centerOfOrbit() const
{
    return m_CenterOfOrbit;
}

SolarSystem::SolarObjects SolarSystem::AbstractSolarObject::object() const
{
    return m_ObjectType;
}
