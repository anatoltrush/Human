#ifndef CYBERSKELETON_H
#define CYBERSKELETON_H

#include "CyberBone.h"
#include "AbstractSkeleton.h"

namespace man{

class CyberSkeleton : public AbstractSkeleton
{
public:
    CyberSkeleton();

    std::map<QString, CyberBone>bones;

    virtual void loadFromJson();
};

}

#endif // CYBERSKELETON_H
