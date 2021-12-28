#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include <GL/gl.h>

#include "Config/Defines.h"
#include "Config/ConfigDefines.h"
#include "Entities/Primitives.h"

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

    Color color;
    Point3F offsetBase;
    float rotationBase = 0.0f;

    float volume = 0.0f;

    void fillProperties();
    void applyRotation();
    void applyOffsets();

    void setColor(int B, int G, int R);
    void drawGLtriangle();
    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
