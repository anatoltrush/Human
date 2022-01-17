#ifndef REARRANGER_H
#define REARRANGER_H

#include "Entities/AbstractSkeleton.h"

namespace man{

class ReArranger
{
public:
    ReArranger();

    AbstractSkeleton* skeleton = nullptr;
};

}

#endif // REARRANGER_H
