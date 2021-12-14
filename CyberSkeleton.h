#ifndef CYBERSKELETON_H
#define CYBERSKELETON_H

#include "CyberBone.h"
#include "AbstractSkeleton.h"

namespace man{

class CyberSkeleton : public AbstractSkeleton
{
public:
    CyberSkeleton();

    CyberBone bones[CYBER_NUM_BONES];
};

}

#endif // CYBERSKELETON_H
