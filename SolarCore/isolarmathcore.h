#ifndef ISOLARMATHCORE_H
#define ISOLARMATHCORE_H

#include <QObject>
#include "solarsystemcore.h"
#include <Qt3DRender/QCamera>

namespace SolarSystem {

    //mathcore interface
    class ISolarMathCore : public QObject {

        Q_OBJECT

    public:

        //base
        ISolarMathCore(QObject* parent = 0);
        virtual ~ISolarMathCore();

        //set camera to control math operation
        virtual void setSolarView(Qt3DRender::QCamera* camera) = 0;

        //update camera settings
        virtual void updateSolarView(SolarObjects object) = 0;

        //update camera new position
        virtual QVector3D getNewSolarViewPosition(SolarObjects object, double radius) = 0;

        //out raiuds of solar object
        virtual float getOuterRadius(SolarObjects object) = 0;

        //calculate current solar object position in space
        virtual QVector3D solarObjectPosition(SolarObjects object) = 0;

        //set solar object current scale
        virtual float setSolarObjectScale(float scale, bool focused = false) = 0;

        //dynamic change solar object scale
        virtual void changeSolarObjectScale(float scale, bool focused = false) = 0;

        //change current speed of solar object
        virtual void changeSolarObjectsSpeed(float speed) = 0;

        //change camera distance
        virtual void changeSolarViewDistance(double distance) = 0;
    };

}

#endif // ISOLARMATHCORE_H
