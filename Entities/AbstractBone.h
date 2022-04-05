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
    virtual ~AbstractBone() override;

    QString name;
    QString pathTo3DModelAbs;

    bool isExist = true;

    Material material = Material::Plastic;

    Angle rotationStart;
    Angle rotationCurrent;
    QVector3D basePoint;
    QVector3D anchorDirect;
    QVector3D anchorDown;

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
    void drawExt() const;

    QMap<QString, QVariant> getPropertyList() const override;

    virtual void serialize();

private:
    QVector3D anchorOffset = QVector3D(0.0f, -10.0f, -20.0f); // config: anchorDown
};

}

#endif // ABSTRACTBONE_H
