#ifndef SOLAR3DVIEWPORT_H
#define SOLAR3DVIEWPORT_H

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QEntity>
#include "solarsystemcore.h"

namespace SolarSystem {

    //class for 3d render
    class Solar3dViewPort : public Qt3DExtras::Qt3DWindow {

        Q_OBJECT

    public:
        Solar3dViewPort(QScreen* screen = nullptr);

    private:

        //scene camera
        Qt3DRender::QCamera* _camera;

        //root entity
        Qt3DCore::QEntity* _root;
    };
}

#endif // SOLAR3DVIEWPORT_H
