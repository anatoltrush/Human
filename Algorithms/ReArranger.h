#ifndef REARRANGER_H
#define REARRANGER_H

#include "Entities/AbstractHuman.h"

namespace man{

class ReArranger
{
public:
    ReArranger();

    Status reArrange(const AbstractHuman &native, AbstractHuman &cyber); // TODO: if have intermediate elements

private:
    void offsetBone(AbstractBone *native, AbstractBone* cyber);
    void scaleBone(AbstractBone *native, AbstractBone* cyber);
    void stretchBone(AbstractBone *native, AbstractBone* cyber);
    void rotateBone(AbstractBone *native, AbstractBone* cyber);
};

}

#endif // REARRANGER_H
