#ifndef CYBERBONE_H
#define CYBERBONE_H

#include "AbstractBone.h"

namespace man{

class CyberBone : public AbstractBone
{
public:
    CyberBone();
    CyberBone(const QString &name, const QString &pathRel);

    int material = -1;

    virtual void serialize();
};

}

#endif // CYBERBONE_H
