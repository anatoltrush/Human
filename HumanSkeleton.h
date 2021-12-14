#ifndef HUMANSKELETON_H
#define HUMANSKELETON_H

#include "HumanBone.h"
#include "AbstractSkeleton.h"

class HumanSkeleton : AbstractSkeleton
{
public:
    HumanSkeleton();

    HumanBone bones[HUMAN_NUM_BONES];
};

#endif // HUMANSKELETON_H
