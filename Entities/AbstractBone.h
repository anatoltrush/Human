#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include <GL/gl.h>

#include "Config/Defines.h"
#include "Config/ConfigDefines.h"
#include "IOpenGL.h"
#include "Entities/Primitives.h"

namespace man{

class AbstractBone : public IOpenGL
{
public:
    AbstractBone();
    virtual ~AbstractBone();

    QString name;
    QString pathTo3DModelRel;
    QString pathTo3DModelAbs;

    bool isHuman = true;
    Material material = Material::Plastic;

    Point3F rotation;
    Point3F parentOffsetPoint;
    Point3F* basePoint = nullptr;
    QString parentName = "na";
    QMap<QString, Point3F> childrenPoints;

    std::vector<AbstractBone*> parentsPointers;
    std::vector<AbstractBone*> childrenPointers;

    QJsonObject boneJsonObject;

    StlObject stlObject;

    void fillProperties();
    void applyRotation();
    void applyOffsets(const Point3F &offset);

    virtual void setColor(uint8_t B, uint8_t G, uint8_t R) override;
    virtual void drawObjectGL() const override;
    void drawBasePoint() const;
    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
