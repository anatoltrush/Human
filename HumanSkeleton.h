#ifndef HUMANSKELETON_H
#define HUMANSKELETON_H

#include "HumanBone.h"
#include "AbstractSkeleton.h"

namespace man{

class HumanSkeleton : AbstractSkeleton
{
public:
    HumanSkeleton();

    std::map<QString, HumanBone>bones;

    virtual void loadFromJson();
};

}

#endif // HUMANSKELETON_H
