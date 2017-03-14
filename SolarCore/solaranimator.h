#ifndef SOLARANIMATOR_H
#define SOLARANIMATOR_H

#include <SolarCore/isolarmathcore.h>
#include <QTimer>

class QPropertyAnimation;
class QParallelAnimationGroup;

namespace SolarSystem {

    //contains ISolarMathCore, and dynamic use it
    class SolarAnimator : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QDateTime solarTime READ solarTime NOTIFY solarTimeChanged)
        Q_PROPERTY(QString solarObjectString READ viewSolarObjectString NOTIFY solarObjectStringChanged)
        Q_PROPERTY(QVector3D viewCenter READ cameraViewCenter WRITE setCameraViewCenter NOTIFY cameraViewCenterChanged)
        Q_PROPERTY(QVector3D viewPosition READ cameraPosition WRITE setCameraPositon NOTIFY cameraPositionChanged)
        Q_PROPERTY(float solarSystemSpeed READ solarSystemSpeed WRITE setSolarSystemSpeed NOTIFY solarSystemSpeedChanged)

    public:

        explicit SolarAnimator(QObject *parent = 0);
        ~SolarAnimator();

        //for math core ref
        ISolarMathCore* mathCore() const;

        //get solar time
        QDateTime solarTime() const;

        //get planet string
        QString viewSolarObjectString() const;

        //get cam view center
        QVector3D cameraViewCenter() const;

        //get cam position
        QVector3D cameraPosition() const;

        //get solar system speed
        float solarSystemSpeed() const;

    private:

        //math core interface
        ISolarMathCore* _mathCore = nullptr;

        //selected solar object
        SolarObjects currentSolarObject = SolarObjects::SolarSystemView;

        //stores string
        QString solarObjStr = SolarObjectsValues::SolarSystem::toString;

        //animation flag
        bool animated = false;

        //animation for view center
        QPropertyAnimation* viewCenterAnimation;

        //animation for position
        QPropertyAnimation* viewPositionAnimation;

        //group animation
        QParallelAnimationGroup* cameraAnimation;

        //speed animation
        QPropertyAnimation* solarSpeedAnimation;

        //store solar systme speed
        float solarSpeed = 0;

    public slots:

        //reset values
        void setDefaultValues();

        //main call for solar system animation
        void animate(float deltaTime);

        //set current solar speed, in percents
        void setSolarSpeed(int value);

        //set current planets size, in percents
        void setSolarSize(int value);

        //set cam view center
        void setCameraViewCenter(int index);

        //set camera view center
        void setCameraViewCenter(QVector3D position);

        //set camera view position
        void setCameraPositon(QVector3D position);

        //set solar system speed
        void setSolarSystemSpeed(float speed);

    signals:
        void solarTimeChanged(QDateTime time);
        void solarObjectStringChanged(QString str);
        void cameraViewCenterChanged(QVector3D);
        void cameraPositionChanged(QVector3D);
        void solarSystemSpeedChanged(float);

    private slots:
        void onAnimationFinished();
    };

}

#endif // SOLARANIMATOR_H
