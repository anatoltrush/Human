#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include <GL/gl.h>

#include "Config/ConfigDefines.h"
#include "Interfaces/IOpenGL.h"
#include "Interfaces/IProperty.h"
#include "Auxiliary/ExtraMath.h"
#include "Auxiliary/Additional.h"

namespace man{

class AbstractBone : public IOpenGL, public IProperty
{
public:
    AbstractBone() = default;
    virtual ~AbstractBone() override = default;

    QString name;
    QString pathTo3DModelAbs;

    bool isExist = true;

    Material material = Material::Plastic;

    Angle rotationStart;
    Angle rotationCurrent;
    Point3FStr basePoint;
    QVector3D anchorDirect;

    Point3FStr parentOffset;
    QMap<QString, QVector3D> childrenPoints;
    QMap<QString, QVector3D> intersections;

    AbstractBone* parentPointer = nullptr;
    std::vector<AbstractBone*> childrenPointers;

    QJsonObject boneJsonObject;

    StlObject stlObject;

    void fillProperties();
    void rotateBone(const QVector3D &centerPoint, const Angle &angles);
    void applyOffsets(const QVector3D &offset);

    QVector3D getHighestPoint();
    QVector3D getLowestPoint();

    QVector3D mainChildrenPoint();

    virtual void drawObjectGL() override;
    void drawBasePoint() const;
    void drawExt() const;

    QMap<QString, QVariant> getPropertyList() const override;

    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
