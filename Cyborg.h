#ifndef CYBORG_H
#define CYBORG_H

#include "CyberSkeleton.h"
#include "AbstractHuman.h"

namespace man{

class Cyborg : public AbstractHuman
{
public:
    Cyborg();

    CyberSkeleton skeleton;
};

}

#endif // CYBORG_H
