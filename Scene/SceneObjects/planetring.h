#ifndef PLANETRING_H
#define PLANETRING_H

#include <solar3dobject.h>

namespace SolarSystem {

    //represents a planet ring, for example saturn and uranus rings
    class PlanetRing : public Solar3dObject
    {
        Q_OBJECT

    public:
        PlanetRing(Qt3DCore::QNode* parent = nullptr);

    protected:
        virtual void update(float deltaTime) override;        
    };
}

#endif // PLANETRING_H
