#ifndef ABSTRACTBONE_H
#define ABSTRACTBONE_H

#include "Defines.h"
#include "ConfigDefines.h"

namespace man{

class AbstractBone
{
public:
    AbstractBone();    

    std::string_view name;
    bool isHuman = true;

    std::vector <AbstractBone*> children;
    std::vector <AbstractBone*> parents;

    virtual void serialize() = 0;
};

}

#endif // ABSTRACTBONE_H
