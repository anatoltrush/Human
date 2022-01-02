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

    std::vector<QString> childrenStr;
    std::vector<AbstractBone*> childrenPtr;
    std::vector<AbstractBone*> parentsPtr;

    QJsonObject boneJsonObject;

    StlObject stlObject;

    Point3F offsetBase;
    float rotationBase = 0.0f;

    void fillProperties();
    void applyRotation();
    void applyOffsets();

    virtual void setColor(uint8_t B, uint8_t G, uint8_t R) override;
    virtual void drawObjectGL() const override;
    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
