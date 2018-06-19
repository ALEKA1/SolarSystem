#ifndef SOLARMATHCORE_H
#define SOLARMATHCORE_H

#include <QObject>
#include <QDateTime>
#include <Qt3DRender/QCamera>
#include <solarsystemcore.h>

namespace SolarSystem
{
    class PlanetsContainer;
    class CameraController;
    class SolarObjectsContainer;

    //base solar math model
    //some realizations used from Qt QML Planets example
    class SolarMathCore : public QObject
    {
        Q_OBJECT

    public:
        explicit SolarMathCore(QObject* parent = nullptr);
        virtual ~SolarMathCore();

        //realize interface
        void setSolarView(Qt3DRender::QCamera *camera);
        Qt3DRender::QCamera* solarView() const;
        float getOuterRadius(SolarObjects object);
        void solarObjectPosition(SolarObjects object);
        QVector3D getNewSolarViewPosition(SolarObjects object, double radius);
        void advanceTime(SolarObjects object);
        float setSolarObjectScale(float scale, bool focused = false);
        void checkSolarObjectScaling(SolarObjects object);
        void changeSolarObjectScale(float scale, bool focused = false);
        void updateSolarView(SolarObjects object);
        void changeSolarObjectsSpeed(float speed);
        void changeSolarViewDistance(double distance);
        void setPlanetsContainer(PlanetsContainer* planetsContainer);
        void changeSolarSystemScale(float scale, bool focused = false);
        void setDeltaTime(float dt);
        QDateTime getTime() const;
        void additionalCalculation();
        void setCameraController(CameraController *controller);
        CameraController* viewController() const;
        void updateSolarViewZoomLimit(SolarObjects object);
        void setSolarViewCenter(QVector3D center);
        QVector3D viewCenter() const;
        QVector3D objectPosition(SolarObjects object);
        QVector3D viewPositionOfObject(SolarObjects object);
        QVector3D viewPosition() const;
        void setSolarViewPosition(QVector3D position);
        float solarSystemSpeed() const;
        QVector3D solarViewStartPositon() const;
        void changeExtraSpeed() const;
        double extraSpeed() const;
        void resetExtraSpeed() const;
        void calculateAllSolarObjectsPosiitons();

    private:

        //forward
        struct Data;

        //main math data
        Data* data;

        ///helper methods

        //rings setup
        void setupPlanetRings();

        //earth cloud calculation
        void atmosphereCalculations();

        //zoom limit calculation
        float calculateZoomLimit(SolarObjects object, float limit);

        //zoom limit calcualtion base
        float calculateZoomLimit(SolarObjects object);
    };
}

#endif // SOLARMATHCORE_H
