#include "earthcloud.h"
#include <Qt3DExtras/QSphereGeometry>
#include <solarsystemcore.h>

SolarSystem::EarthCloud::EarthCloud(Qt3DCore::QNode* parent):
    EarthCloudBase(parent)
{
    auto sphereGeometry = new Qt3DExtras::QSphereGeometry();

    //setup geometry
    sphereGeometry->setRadius(PlanetSettings::radius);
    sphereGeometry->setGenerateTangents(PlanetSettings::generateTangents);
    sphereGeometry->setRings(PlanetSettings::rings);
    sphereGeometry->setSlices(PlanetSettings::slices);

    mesh().setGeometry(sphereGeometry);

#ifndef QT3D_MATERIALS
    _material->setDiffuseTextureSource(":/Resources/Images/earthcloudmapcolortrans.png");
#else
    diffuse().setSource(QUrl::fromLocalFile(":/Resources/Images/earthcloudmapcolortrans.png"));
    _material->diffuse()->setGenerateMipMaps(true);

    Qt3DRender::QTextureImage* normalMap = new Qt3DRender::QTextureImage();
    normalMap->setSource(QUrl::fromLocalFile(":/Resources/Images/earthcloudmapcolortransnormal.png"));
    material().normal()->addTextureImage(normalMap);

    _material->diffuse()->setGenerateMipMaps(true);
    _material->diffuse()->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    _material->diffuse()->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    _material->diffuse()->setMaximumAnisotropy(16.0f);

    _material->normal()->setGenerateMipMaps(true);
    _material->normal()->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    _material->normal()->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    _material->normal()->setMaximumAnisotropy(16.0f);
#endif
}

void SolarSystem::EarthCloud::update(float deltaTime)
{
    Q_UNUSED(deltaTime)

    //create matrix
    auto matrix = QMatrix4x4();

    //set position
    matrix.translate(QVector3D(_x, _y, _z));

    //rotate
    matrix.rotate(_tilt, SolarValues::tiltAxis);
    matrix.rotate(_roll, SolarValues::rollAxis);

    //ring scale
    matrix.scale(_r);

    transform().setMatrix(matrix);
}
