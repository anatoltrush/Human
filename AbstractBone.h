#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include "Defines.h"
#include "Primitives.h"
#include "ConfigDefines.h"

namespace man{

class AbstractBone
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

    float volume = 0.0f;

    void fillProperties();
    void applyRotation();
    void applyOffsets();

    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
