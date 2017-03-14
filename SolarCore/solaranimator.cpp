#include "solaranimator.h"
#include <SolarCore/solarmathcore.h>
#include <Parser/solarparser.h>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTimer>

SolarSystem::SolarAnimator::SolarAnimator(QObject *parent):
    QObject(parent)
{
    _mathCore = new SolarMathCore();
    viewCenterAnimation = new QPropertyAnimation(this);
    viewPositionAnimation = new QPropertyAnimation(this);
    solarSpeedAnimation = new QPropertyAnimation(this);
    cameraAnimation = new QParallelAnimationGroup(this);

    viewCenterAnimation->setTargetObject(this);
    viewCenterAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuint));

    viewPositionAnimation->setTargetObject(this);
    viewPositionAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InOutQuint));

    solarSpeedAnimation->setTargetObject(this);
    solarSpeedAnimation->setEasingCurve(QEasingCurve(QEasingCurve::InExpo));

    //animation add
    cameraAnimation->addAnimation(viewCenterAnimation);
    cameraAnimation->addAnimation(viewPositionAnimation);

    QObject::connect(cameraAnimation, &QParallelAnimationGroup::finished, this, &SolarAnimator::onAnimationFinished);
}

SolarSystem::SolarAnimator::~SolarAnimator()
{
    delete _mathCore;
}

SolarSystem::ISolarMathCore *SolarSystem::SolarAnimator::mathCore() const
{
    return _mathCore;
}

QDateTime SolarSystem::SolarAnimator::solarTime() const
{
    return _mathCore->getTime();
}

QString SolarSystem::SolarAnimator::viewSolarObjectString() const
{
    return solarObjStr;
}

QVector3D SolarSystem::SolarAnimator::cameraViewCenter() const
{
    return _mathCore->viewCenter();
}

QVector3D SolarSystem::SolarAnimator::cameraPosition() const
{
    return _mathCore->viewPosition();
}

float SolarSystem::SolarAnimator::solarSystemSpeed() const
{
    return _mathCore->solarSystemSpeed();
}

void SolarSystem::SolarAnimator::setDefaultValues()
{
    _mathCore->changeSolarObjectsSpeed(SolarSystem::SolarValues::startSpeed);
    _mathCore->changeSolarSystemScale(SolarSystem::SolarValues::startSize);
}

void SolarSystem::SolarAnimator::animate(float deltaTime)
{
    //set delta time to math core
    _mathCore->setDeltaTime(deltaTime);

    //calculate time
    _mathCore->advanceTime(currentSolarObject);

    //update solar objects position
    auto updateCount = static_cast<int>(SolarObjects::Pluto);

    for (int i = 0; i < updateCount; ++i)
        _mathCore->solarObjectPosition((SolarObjects)i);

    _mathCore->ringsCalculation();

    if (!animated)
        _mathCore->updateSolarView(currentSolarObject);

    emit solarTimeChanged(_mathCore->getTime());
}

void SolarSystem::SolarAnimator::setSolarSpeed(int value)
{
    float coeff = 1.0f;

    if (value < 50)
        coeff = value/500.0f;
    else if (value > 50)
        coeff = value/10.0f;
    else
        coeff = value/50.0f;

    _mathCore->changeSolarObjectsSpeed(SolarValues::startSpeed * coeff);
}

void SolarSystem::SolarAnimator::setSolarSize(int value)
{
    float coeff = value/50.0f;
    _mathCore->changeSolarSystemScale(SolarValues::startSize * coeff);
}

void SolarSystem::SolarAnimator::setCameraViewCenter(int index)
{
    if (!animated)
    {
        auto obj = SolarParser::parsePlanetListIndex(index);

        if (obj != currentSolarObject)
        {
            currentSolarObject = obj;
            solarObjStr = SolarParser::parseSolarObjectToString(currentSolarObject);

            emit solarObjectStringChanged(solarObjStr);

            _mathCore->updateSolarViewZoomLimit(currentSolarObject);

            animated = true;

            //setup view animation
            viewCenterAnimation->setPropertyName("viewCenter");
            viewCenterAnimation->setDuration(1500);
            viewCenterAnimation->setStartValue(_mathCore->viewCenter());
            viewCenterAnimation->setEndValue(_mathCore->objectPosition(currentSolarObject));

            viewPositionAnimation->setPropertyName("viewPosition");
            viewPositionAnimation->setStartValue(_mathCore->viewPosition());

            if (obj != SolarObjects::SolarSystemView)
            {
                //setup position animation
                viewPositionAnimation->setDuration(2500);
                viewPositionAnimation->setEndValue(_mathCore->viewPositionOfObject(currentSolarObject));
            }
            else
            {
                //setup position animation
                viewCenterAnimation->setDuration(3000);

                viewPositionAnimation->setDuration(2500);
                viewPositionAnimation->setEndValue(_mathCore->solarViewStartPositon());
            }

            //save speed
            solarSpeed = _mathCore->solarSystemSpeed();

            QTimer::singleShot(1500, Qt::TimerType::PreciseTimer, [&]{
                solarSpeedAnimation->setPropertyName("solarSystemSpeed");
                solarSpeedAnimation->setDuration(1000);
                solarSpeedAnimation->setStartValue(0);
                solarSpeedAnimation->setEndValue(solarSpeed);
                solarSpeedAnimation->start();
            });

            //reset soalr system speed
            _mathCore->changeSolarObjectsSpeed(0);

            cameraAnimation->start();
        }
    }
}

void SolarSystem::SolarAnimator::setCameraViewCenter(QVector3D position)
{
    _mathCore->setSolarViewCenter(position);

    emit cameraViewCenterChanged(position);
}

void SolarSystem::SolarAnimator::setCameraPositon(QVector3D position)
{
    _mathCore->setSolarViewPosition(position);

    emit cameraPositionChanged(position);
}

void SolarSystem::SolarAnimator::setSolarSystemSpeed(float speed)
{
    _mathCore->changeSolarObjectsSpeed(speed);

    emit solarSystemSpeedChanged(speed);
}

void SolarSystem::SolarAnimator::onAnimationFinished()
{
    animated = false;
}
