#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include <string>

#include "Defines.h"

namespace man{

class AbstractBone
{
public:
    AbstractBone();

    std::string name;

    virtual void serialize() = 0;
};

}

#endif // ABSTRACTBONE_H
