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

    float calcAngleY360(const QVector3D &starX, const QVector3D &center, const QVector3D &starY, const QVector3D &pt);
};

}

#endif // REARRANGER_H
