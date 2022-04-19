#ifndef ABSTRACTREARRANGER_H
#define ABSTRACTREARRANGER_H

#include "Entities/AbstractHuman.h"

namespace man{

struct anchorPoint
{
    QVector3D coords;
    QString aliasName;
};

class AbstractReArranger
{
public:
    AbstractReArranger() = default;
    virtual ~AbstractReArranger() = default;

    std::vector<anchorPoint> anchorPoints;

    virtual Status reArrange(AbstractHuman &cyber) = 0;

protected:
    virtual void adjustPoints() = 0;

    virtual void offsetGroups() = 0;
    virtual void scaleGroups() = 0;
    virtual void rotateGroups() = 0;
};

}

#endif // ABSTRACTREARRANGER_H
