#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include <GL/gl.h>

#include "Config/ConfigDefines.h"
#include "Interfaces/IOpenGL.h"
#include "Interfaces/IProperty.h"
#include "Algorithms/ExtraMath.h"

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

    Angle rotation;
    Point3F* basePoint = nullptr;
    std::vector<Point3F> interSects;

    Point3FStr parentOffset;
    QMap<QString, Point3F> childrenPoints;

    std::vector<AbstractBone*> parentsPointers;
    std::vector<AbstractBone*> childrenPointers;

    QJsonObject boneJsonObject;

    StlObject stlObject;

    void fillProperties();
    void rotateBone(const Point3F &basePoint, const Angle &angles);
    void applyOffsets(const Point3F &offset);

    Point3F getHighestPoint();
    Point3F getLowestPoint();

    virtual void drawObjectGL() const override;
    void drawBasePoint() const;

    QMap<QString, QVariant> getPropertyList() const override;

    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
