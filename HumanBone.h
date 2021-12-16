#ifndef HUMANBONE_H
#define HUMANBONE_H

#include "AbstractBone.h"

namespace man{

class HumanBone : public AbstractBone
{
public:
    HumanBone();
    HumanBone(const std::string_view & name);

    virtual void serialize();
};

}

#endif // HUMANBONE_H
