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
    AbstractBone();
    virtual ~AbstractBone();

    QString name;
    QString pathTo3DModelAbs;

    bool isExist = true;

    Material material = Material::Plastic;

    Angle rotationStart;
    Angle rotationCurrent;
    QVector3D basePoint;

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

    virtual void drawObjectGL() override;
    void drawBasePoint() const;

    QMap<QString, QVariant> getPropertyList() const override;

    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
