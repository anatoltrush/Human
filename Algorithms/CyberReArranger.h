#ifndef CYBERREARRANGER_H
#define CYBERREARRANGER_H

#include "Algorithms/AbstractReArranger.h"

namespace man{

class CyberReArranger : public AbstractReArranger
{
public:
    CyberReArranger() = default;
    virtual ~CyberReArranger() override = default;

    Status reArrange(const AbstractHuman &native, AbstractHuman &cyber);

    virtual Status reArrange(AbstractHuman &cyber) override;

private:
    void offsetBone(AbstractBone *native, AbstractBone* cyber);
    void scaleBone(AbstractBone *native, AbstractBone* cyber);
    void rotateBone(man::AbstractBone *native, man::AbstractBone *cyber); // TODO: if several children points

    float calcAngleY360(const QVector3D &starX, const QVector3D &center, const QVector3D &starY, const QVector3D &pt);

protected:
    virtual void adjustPoints() override;

    virtual void offsetGroups() override;
    virtual void scaleGroups() override;
    virtual void rotateGroups() override;
};

}

#endif // CYBERREARRANGER_H
