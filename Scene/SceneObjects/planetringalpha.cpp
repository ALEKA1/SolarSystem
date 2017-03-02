#include "planetringalpha.h"
#include <Qt3DRender/QTextureWrapMode>

SolarSystem::PlanetRingAlpha::PlanetRingAlpha(Qt3DCore::QNode* parent):
    BaseVisualSolarObject(parent),
  _picker(new Qt3DRender::QObjectPicker),
  _material(new Qt3DExtras::QNormalDiffuseMapAlphaMaterial),
  _diffuse(new Qt3DRender::QTextureImage())
{
    wrapMode.setX(Qt3DRender::QTextureWrapMode::WrapMode::Repeat);
    wrapMode.setY(Qt3DRender::QTextureWrapMode::WrapMode::Repeat);

    _material->diffuse()->setWrapMode(wrapMode);
    _material->diffuse()->setGenerateMipMaps(true);
    _material->diffuse()->setMagnificationFilter(Qt3DRender::QAbstractTexture::Linear);
    _material->diffuse()->setMinificationFilter(Qt3DRender::QAbstractTexture::LinearMipMapLinear);
    _material->diffuse()->setMaximumAnisotropy(16.0f);

    _material->diffuse()->addTextureImage(_diffuse);

    _picker->setDragEnabled(false);
    _picker->setHoverEnabled(false);
    _picker->setEnabled(true);

    addComponent(_material);
    addComponent(_picker);

    mesh().setSource(QUrl::fromLocalFile(":/Resources/Meshes/ring.obj"));
}

Qt3DRender::QObjectPicker &SolarSystem::PlanetRingAlpha::picker() const
{
  return *_picker;
}

Qt3DExtras::QNormalDiffuseMapAlphaMaterial &SolarSystem::PlanetRingAlpha::material() const
{
  return *_material;
}

Qt3DRender::QTextureImage& SolarSystem::PlanetRingAlpha::diffuse() const
{
    return *_diffuse;
}

void SolarSystem::PlanetRingAlpha::update(float deltaTime)
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
