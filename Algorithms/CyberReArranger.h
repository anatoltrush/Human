#ifndef CYBERREARRANGER_H
#define CYBERREARRANGER_H

#include "Entities/AbstractHuman.h"

namespace man{

class CyberReArranger
{
public:
    CyberReArranger() = default;

    Status reArrange(const AbstractHuman &native, AbstractHuman &cyber);

private:
    void offsetBone(AbstractBone *native, AbstractBone* cyber);
    void scaleBone(AbstractBone *native, AbstractBone* cyber);
    void rotateBone(man::AbstractBone *native, man::AbstractBone *cyber); // TODO: if several children points

    float calcAngleY360(const QVector3D &starX, const QVector3D &center, const QVector3D &starY, const QVector3D &pt);
};

}

#endif // CYBERREARRANGER_H
