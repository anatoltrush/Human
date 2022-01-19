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
    Status reArrangeDistances(const AbstractHuman &native, AbstractHuman &cyber);
    Status reArrangeAngle(const AbstractHuman &native, AbstractHuman &cyber);
};

}

#endif // REARRANGER_H
