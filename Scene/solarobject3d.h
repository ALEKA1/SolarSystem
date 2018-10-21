#ifndef SOLAROBJECT3D_H
#define SOLAROBJECT3D_H

#include <functional>
#include <solarsystemcore.h>
#include <Qt3DCore/QEntity>

namespace Qt3DCore
{
    class QTransform;
}

namespace Qt3DLogic
{
    class QFrameAction;
}

namespace Qt3DRender
{
    class QGeometryRenderer;
    class QObjectPicker;
    class QMaterial;
}

namespace SolarSystem
{
    //types
    using LogicPtr = std::function<void(float)>;
    using Logic = std::vector<LogicPtr>;

    ///base visual object on the scene
    class SolarObject3D : public Qt3DCore::QEntity
    {
        Q_OBJECT

    public:

        ///creates 3d object
        explicit SolarObject3D(Qt3DCore::QNode* parent = nullptr);

    protected:

        //frame tick for solar object logic programming
        virtual void update(float deltaTime) = 0;

        //sets material type
        void setMaterialType(SolarMaterials material);

    public:

        //logic
        void addLogic(LogicPtr func);
        void clearLogic();

        //position in space
        Qt3DCore::QTransform* transform() const;

        //get renderer
        Qt3DRender::QGeometryRenderer* renderer() const;

        //get picker
        Qt3DRender::QObjectPicker* picker() const;

        //returns current object type
        SolarObjects solarType() const;

        //set solar type
        void setSolarType(SolarObjects type);

        //returns object material type
        SolarMaterials materialType() const;

        //returns object material
        Qt3DRender::QMaterial* material() const;

        //control
        float r() const;
        void setR(float r);

        float x() const;
        void setX(float x);

        float y() const;
        void setY(float y);

        float z() const;
        void setZ(float z);

        float roll() const;
        void setRoll(float roll);

        float tilt() const;
        void setTilt(float tilt);

    protected:

        //logical
        SolarSystem::Logic m_Logic;
        Qt3DLogic::QFrameAction* m_FrameAction;
        Qt3DRender::QObjectPicker* m_Picker;

        //Qt3D components
        Qt3DCore::QTransform* m_Transform;
        Qt3DRender::QGeometryRenderer* m_Renderer;
        Qt3DRender::QMaterial* m_Material;

        //main data
        SolarSystem::SolarObjects m_SolarType;
        SolarSystem::SolarMaterials m_MaterialType = SolarMaterials::None;
        float m_R = 0;
        float m_X = 0;
        float m_Y = 0;
        float m_Z = 0;
        float m_Roll = 0;
        float m_Tilt = 0;
    };
}

#endif // SOLAROBJECT3D_H
