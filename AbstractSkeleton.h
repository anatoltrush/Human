#ifndef ABSTRACTSKELETON_H
#define ABSTRACTSKELETON_H

#include <QString>

#include "Config.h"
#include "AbstractBone.h"
#include "CyberBone.h"
#include "StlReader.h"

namespace man{

class AbstractSkeleton
{
public:
    AbstractSkeleton();
    virtual ~AbstractSkeleton();

    QString name;    

    QMap<QString, AbstractBone*>bones;

    bool isConstructDone = false;

    StlReader stlReader;

    virtual int loadFromJson(const Config& config);
    virtual int construct();
};

}

#endif // ABSTRACTSKELETON_H
