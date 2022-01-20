#ifndef REARRANGER_H
#define REARRANGER_H

#include "Entities/AbstractHuman.h"

namespace man{

class ReArranger
{
public:
    ReArranger();

    Status reArrange(const AbstractHuman &native, AbstractHuman &cyber);

private:
    Status reArrangeDistances(const AbstractHuman &native, AbstractHuman &cyber); // TODO: if have intermediate elements
    Status reArrangeAngle(const AbstractHuman &native, AbstractHuman &cyber);

    void moveAndStretch(AbstractBone *native, AbstractBone* cyber);// FIXME: error, only first work
};

}

#endif // REARRANGER_H
