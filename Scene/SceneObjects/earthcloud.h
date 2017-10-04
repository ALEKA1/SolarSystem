#ifndef EARTHCLOUD_H
#define EARTHCLOUD_H

#include <solarsystemcore.h>

#ifndef QT3D_MATERIALS
#include <solar3dobject.h>
#else
#include <solar3dalphaobject.h>
#endif

namespace SolarSystem
{
#ifndef QT3D_MATERIALS
    using EarthCloudBase = Solar3dObject;
#else
    using EarthCloudBase = Solar3DAlphaObject;
#endif

    //represents earth cloud mesh
    class EarthCloud : public EarthCloudBase
    {
        Q_OBJECT

    public:
        EarthCloud(Qt3DCore::QNode* parent = nullptr);

    protected:
        virtual void update(float deltaTime) override;
    };
}

#endif // EARTHCLOUD_H
