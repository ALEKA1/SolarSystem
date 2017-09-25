#ifndef PLANETSCONTAINER_H
#define PLANETSCONTAINER_H

#include <QObject>
#include <Interface/ivisualsolarobject.h>
#include <map>

namespace Qt3DRender
{
    class QTexture2D;
}

namespace SolarSystem
{
    //array type
    using PlanetArray = std::map<SolarObjects, IVisualSolarObject*>;

#ifndef QT3D_MATERIALS
    //forward
    class SolarLight;
    class SolarObjectEffect;
    class SolarShadowEffect;
    class SolarDiffuseEffect;
#endif

    //contains all 3D planets
    class PlanetsContainer : public QObject
    {
        Q_OBJECT

    public:

        explicit PlanetsContainer(Qt3DCore::QNode* root = nullptr, QObject* parent = nullptr);
        ~PlanetsContainer();

    private:

        //main fields
        PlanetArray planetContainer;
        Qt3DCore::QNode* rootNode;

        //helper
        void initialize(Qt3DCore::QNode *root);

#ifndef QT3D_MATERIALS
        //effects
        SolarObjectEffect* _baseEffect;
        SolarShadowEffect* _shadowEffect;
        SolarDiffuseEffect* _diffuseEffect;
#endif

    public:

        //get planets number
        int planetsNumber() const;

        //get all planets
        PlanetArray planets() const;

#ifndef QT3D_MATERIALS
        //get effects
        SolarObjectEffect* baseEffect() const;
        SolarShadowEffect* shadowEffect() const;

        //set light
        void setLight(SolarLight* light);
        void setShadowTexture(Qt3DRender::QTexture2D* texture);
        void initEffects();
#endif

    signals:

        //if we pressed on planet
        void planetClicked(IVisualSolarObject*);

        //pressed coords
        void coordClicked(QVector3D);

    private slots:

        //on planet pick
        void onObjectPick(Qt3DRender::QPickEvent* pick);
    };
}

#endif // PLANETSCONTAINER_H
