#ifndef HUMANBONE_H
#define HUMANBONE_H

#include "AbstractBone.h"

namespace man{

class HumanBone : public AbstractBone
{
public:
    HumanBone();

    virtual void serialize();
};

}

#endif // HUMANBONE_H
