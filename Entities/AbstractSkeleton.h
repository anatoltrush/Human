#ifndef ABSTRACTSKELETON_H
#define ABSTRACTSKELETON_H

#include <QString>

#include "Config/Config.h"
#include "AbstractBone.h"
#include "CyberBone.h"
#include "HumanBone.h"
#include "Algorithms/StlHandler.h"

namespace man{

class AbstractSkeleton
{
public:
    AbstractSkeleton();
    virtual ~AbstractSkeleton();

    QString name;    

    QMap<QString, AbstractBone*>bones;

    bool isConstructDone = false;

    StlHandler stlReader;

    virtual man::Status loadFromJson(const Config& config, bool isHuman);
    virtual man::Status construct();
};

}

#endif // ABSTRACTSKELETON_H
