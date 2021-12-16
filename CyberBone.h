#ifndef CYBERBONE_H
#define CYBERBONE_H

#include "AbstractBone.h"

namespace man{

class CyberBone : public AbstractBone
{
public:
    CyberBone();
    CyberBone(const std::string_view & name);

    virtual void serialize();
};

}

#endif // CYBERBONE_H
