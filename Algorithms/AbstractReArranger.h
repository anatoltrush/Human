#ifndef ABSTRACTREARRANGER_H
#define ABSTRACTREARRANGER_H

#include "Entities/AbstractHuman.h"

namespace man{

class AbstractReArranger
{
public:
    AbstractReArranger() = default;
    virtual ~AbstractReArranger() = default;

    QMap<QString, QVector3D> anchorPoints;
    QMap<QString, std::vector<AbstractBone*>> groups;

    virtual Status reArrange(AbstractHuman &cyber) = 0;

private:
    virtual void adjustPoints() = 0;

    virtual void offsetGroups() = 0;
    virtual void scaleGroups() = 0;
    virtual void rotateGroups() = 0;

    virtual void makeGroups(AbstractHuman &human) = 0;
};

}

#endif // ABSTRACTREARRANGER_H
