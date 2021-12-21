#ifndef HUMANSKELETON_H
#define HUMANSKELETON_H

#include "HumanBone.h"
#include "AbstractSkeleton.h"

namespace man{

class HumanSkeleton : public AbstractSkeleton
{
public:
    HumanSkeleton();

    std::map<QString, HumanBone>bones;

};

}

#endif // HUMANSKELETON_H
