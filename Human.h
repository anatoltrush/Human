#ifndef HUMAN_H
#define HUMAN_H

#include "HumanSkeleton.h"
#include "AbstractHuman.h"

namespace man{

class Human : public AbstractHuman
{
public:
    Human();

    HumanSkeleton skeleton;
};

}

#endif // HUMAN_H
