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
    void rotateBone(man::AbstractBone *native, man::AbstractBone *cyber);
    void stretchAndRotateBone(AbstractBone *native, AbstractBone* cyber);

    float convert2angTo360Deg(float angleX, float angleY);
};

}

#endif // REARRANGER_H
