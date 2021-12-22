#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include "Defines.h"
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

    std::vector<QString> childrenStr;
    std::vector<AbstractBone*> childrenPtr;
    std::vector<AbstractBone*> parentsPtr;

    QJsonObject boneJsonObject;

    void fillProperties();
    void defineChildren();
    void defineParents();
    void calcNewBasePoint();

    virtual void serialize();
};

}

#endif // ABSTRACTBONE_H
