#ifndef SOLARSYSTEMCORE_H
#define SOLARSYSTEMCORE_H

#include <QString>
#include <QStringList>
#include <QVector3D>
#include <vector>

namespace SolarSystem
{
    // store all query strings for db
    struct SolarStrings
    {
        // db type
        inline static const QString qSqlLite = "QSQLITE";

        // help
        inline static const QString dbName = "SolarSystem";
        inline static const QString dbFileName = "SolarDB.db";
        inline static const QString dbFolder = "/Database/";

        // db fields
        inline static const QString nameField = "Name";
        inline static const QString type = "SolarType";
        inline static const QString orbitalSpeed = "OrbitalSpeed";
        inline static const QString mass = "Mass";
        inline static const QString meanRadius = "MeanRadius";
        inline static const QString surfaceTemp = "Temperature";
        inline static const QString surfaceGravity = "Gravity";
        inline static const QString volume = "Volume";
        inline static const QString siderealPeriod = "SiderealPeriod";
        inline static const QString orbitalPeriod = "OrbitalPeriod";
        inline static const QString description = "Description";

        // SQL commands
        inline static const QString select = "SELECT ";
        inline static const QString from = " FROM ";
        inline static const QString where = " WHERE ";
        inline static const QString like = " LIKE";
        inline static const QString all = "*";

        static QString likeObject(const QString& object);

        // string representation of object type
        inline static const QString planet = "Planet";
        inline static const QString dwarfPlanet = "Dwarf planet";
        inline static const QString star = "Star";
        inline static const QString moon = "Moon";
        inline static const QString ring = "Ring";
        inline static const QString solarSystemBody = "Solar system body";
        inline static const QString galaxy = "Galaxy";
        inline static const QString asteroid = "Asteroid";

        // add object types
    };

    // store different values for code help
    struct SolarValues
    {
        inline static const int zero = 0;
        inline static const int solarDistance = 2600000;
        inline static const float auScale = 149597.870700f;
        inline static const float saturnOuterRadius = 120.700f;
        inline static const float uranusOuterRadius = 40.0f;
        inline static const float startSize = 1800;
        inline static const float startSpeed = 1000000.0f;

        // time scale values
        inline static const int year = 2000;
        inline static const int month = 1;
        inline static const int day = 1;

        // vector values
        inline static const QVector3D rollAxis = QVector3D(0, 1, 0);
        inline static const QVector3D tiltAxis = QVector3D(0, 0, 1);

        // db fields
    };

    enum SolarFields
    {
        SolarType,
        Name,
        OrbitalSpeed,
        Mass,
        MeanRadius,
        Temperature,
        Gravity,
        Volume,
        SiderealPeriod,
        OrbitalPeriod,
        Description
    };

    // solar system object type
    enum class SolarSystemObjectType
    {
        SolarSystemBody,
        Planet,
        DwarfPlanet,
        Moon,
        Ring,
        Star,
        Asteroid,
        Galaxy
    };

    // enum of all solar objects
    // add new if you need
    enum class SolarObjects
    {
        Sun,
        Mercury,
        Venus,
        Earth,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune,
        Moon,
        Pluto,

        // add here
        SaturnRing,
        UranusRing,
        EarthCloud,

        // calculate number
        SolarSystemView
    };

    // all material types used in solar system project
    enum class SolarMaterials
    {
        None,
        Diffuse,
        DiffuseSpecular,
        NormalDiffuse,
        NormalDiffiseSpecular,
        NormalDiffuseAplha,
        Phong,
        PhongAlpha,
        Unlit
    };

    // store default camera settings
    namespace CameraSettings
    {
        // camera up vector
        const QVector3D defaultUp(0, 1, 0);

        // default position
        const QVector3D defaultCameraPosition(SolarValues::solarDistance, SolarValues::solarDistance, SolarValues::solarDistance);

        // near plane/far plane settings
        const float nearPlane = 2500000.0;
        const float farPlane = 20000000.0;

        // fov
        const int fieldOfView = 60;
    }

    // for planet class
    namespace PlanetSettings
    {
        const float radius = 1.0f;
        const bool generateTangents = true;
        const int rings = 64;
        const int slices = 64;
    }

    // params for DB fields
    namespace DbParams
    {
        const QStringList paramList = {"", "", "km/s", "kg", "km", "K", "m/s2", "km3", "d", "d", ""};
    }

    // planets math values
    namespace SolarObjectsValues
    {
        // Planet Data
        // radius - planet radius
        // tilt - planet axis angle
        // N1/2 - longitude of the ascending node
        // i1/2 - inclination to the ecliptic (plane of the Earth's orbit)
        // w1/2 - argument of perihelion
        // a1/2 - semi-major axis, or mean distance from Sun
        // e1/2 - eccentricity (0=circle, 0-1=ellipse, 1=parabola)
        // M1/2 - mean anomaly (0 at perihelion; increases uniformly with time)
        // period - sidereal rotation period
        // centerOfOrbit - the planet in the center of the orbit
        // (orbital elements based on http://www.stjarnhimlen.se/comp/ppcomp.html)

        // solar system values
        namespace SolarSystem
        {
            const QString toString = "Solar System";
        }

        // sun values
        namespace Sun
        {
            const float radius = 694.439f;
            const float tilt = 63.87f;
            const float period = 25.05f;
            const QString toString = "Sun";
        }

        // mercury values
        namespace Mercury
        {
            const float radius = 2.433722f;
            const float tilt = 0.04f;
            const float N1 = 48.3313f;
            const float N2 = 0.0000324587f;
            const float i1 = 7.0047f;
            const float i2 = 0.0000000500f;
            const float w1 = 29.1241f;
            const float w2 = 0.0000101444f;
            const float a1 = 0.387098f;
            const float a2 = 0;
            const float e1 = 0.205635f;
            const float e2 = 0.000000000559f;
            const float M1 = 168.6562f;
            const float M2 = 4.0923344368f;
            const float period = 58.646f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Mercury";
        }

        // venus values
        namespace Venus
        {
            const float radius = 6.046079f;
            const float tilt = 177.36f;
            const float N1 = 76.6799f;
            const float N2 = 0.0000246590f;
            const float i1 = 3.3946f;
            const float i2 = 0.0000000275f;
            const float w1 = 54.8910f;
            const float w2 = 0.0000138374f;
            const float a1 = 0.723330f;
            const float a2 = 0;
            const float e1 = 0.006773f;
            const float e2 = -0.000000001302f;
            const float M1 = 48.0052f;
            const float M2 = 1.6021302244f;
            const float period = 243.0185f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Venus";
        }

        // earth values
        namespace Earth
        {
            const float radius = 6.371f;
            const float tilt = 25.44f;
            const float N1 = 174.873f;
            const float N2 = 0;
            const float i1 = 0.00005f;
            const float i2 = 0;
            const float w1 = 102.94719f;
            const float w2 = 0;
            const float a1 = 1;
            const float a2 = 0;
            const float e1 = 0.01671022f;
            const float e2 = 0;
            const float M1 = 357.529f;
            const float M2 = 0.985608f;
            const float period = 0.997f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Earth";
        }

        // mars values
        namespace Mars
        {
            const float radius = 3.389372f;
            const float tilt = 25.19f;
            const float N1 = 49.5574f;
            const float N2 = 0.0000211081f;
            const float i1 = 1.8497f;
            const float i2 = -0.0000000178f;
            const float w1 = 286.5016f;
            const float w2 = 0.0000292961f;
            const float a1 = 1.523688f;
            const float a2 = 0;
            const float e1 = 0.093405f;
            const float e2 = 0.000000002516f;
            const float M1 = 18.6021f;
            const float M2 = 0.5240207766f;
            const float period = 1.025957f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Mars";
        }

        // jupiter values
        namespace Jupier
        {
            const float radius = 71.41254f;
            const float tilt = 3.13f;
            const float N1 = 100.4542f;
            const float N2 = 0.0000276854f;
            const float i1 = 1.3030f;
            const float i2 = -0.0000001557f;
            const float w1 = 273.8777f;
            const float w2 = 0.0000164505f;
            const float a1 = 5.20256f;
            const float a2 = 0;
            const float e1 = 0.048498f;
            const float e2 = 0.000000004469f;
            const float M1 = 19.8950f;
            const float M2 = 0.0830853001f;
            const float period = 0.4135f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Jupiter";
        }

        // saturn values
        namespace Saturn
        {
            const float radius = 60.19958f;
            const float tilt = 26.73f;
            const float N1 = 113.6634f;
            const float N2 = 0.0000238980f;
            const float i1 = 2.4886f;
            const float i2 = -0.0000001081f;
            const float w1 = 339.3939f;
            const float w2 = 0.0000297661f;
            const float a1 = 9.55475f;
            const float a2 = 0;
            const float e1 = 0.055546f;
            const float e2 = -0.000000009499f;
            const float M1 = 316.9670f;
            const float M2 = 0.0334442282f;
            const float period = 0.4395f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Saturn";
        }

        // uranus values
        namespace Uranus
        {
            const float radius = 25.5286f;
            const float tilt = 97.77f;
            const float N1 = 74.0005f;
            const float N2 = 0.000013978f;
            const float i1 = 0.7733f;
            const float i2 = 0.000000019f;
            const float w1 = 96.6612f;
            const float w2 = 0.000030565f;
            const float a1 = 19.18171f;
            const float a2 = -0.0000000155f;
            const float e1 = 0.047318f;
            const float e2 = 0.00000000745f;
            const float M1 = 142.5905f;
            const float M2 = 0.011725806f;
            const float period = 0.71833f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Uranus";
        }

        // neptune values
        namespace Neptune
        {
            const float radius = 24.73859f;
            const float tilt = 28.32f;
            const float N1 = 131.7806f;
            const float N2 = 0.000030173f;
            const float i1 = 1.7700f;
            const float i2 = -0.000000255f;
            const float w1 = 272.8461f;
            const float w2 = 0.000006027f;
            const float a1 = 30.05826f;
            const float a2 = 0.00000003313f;
            const float e1 = 0.008606f;
            const float e2 = 0.00000000215f;
            const float M1 = 260.2471f;
            const float M2 = 0.005995147f;
            const float period = 0.6713f;
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Neptune";
        }

        // pluto values
        namespace Pluto
        {
            const float radius = 1.187f;            //radius
            const float tilt = 120.00f;
            const float N1 = 110.30347f;            //longitude
            const float N2 = 0;
            const float i1 = 17.14175f;             //inclination
            const float i2 = 0;
            const float w1 = 113.834f;              //perihelion
            const float w2 = 0;
            const float a1 = 39.48168677f;          //semi-major axis
            const float a2 = 0;
            const float e1 = 0.24880766f;           //eccentricity
            const float e2 = 0;
            const float M1 = 14.53f;                //mean anomaly
            const float M2 = 0;
            const float period = 6.387230f;         //siderial rotation period
            const SolarObjects centerOfOrbit = SolarObjects::Sun;
            const QString toString = "Pluto";
        }

        // moon values
        namespace Moon
        {
            const float radius = 1.5424f;
            const float tilt = 28.32f;
            const float N1 = 125.1228f;
            const float N2 = -0.0529538083f;
            const float i1 = 5.1454f;
            const float i2 = 0;
            const float w1 = 318.0634f;
            const float w2 = 0.1643573223f;
            const float a1 = 0.273f;
            const float a2 = 0;
            const float e1 = 0.054900f;
            const float e2 = 0;
            const float M1 = 115.3654f;
            const float M2 = 13.0649929509f;
            const float period = 27.321582f;
            const SolarObjects centerOfOrbit = SolarObjects::Earth;
            const QString toString = "Moon";
        }
    }
}


#endif // SOLARSYSTEMCORE_H
