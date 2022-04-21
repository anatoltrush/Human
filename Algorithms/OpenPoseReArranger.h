#ifndef OPENPOSEREARRANGER_H
#define OPENPOSEREARRANGER_H

#include "Algorithms/AbstractReArranger.h"

namespace man{

class OpenPoseReArranger : public AbstractReArranger
{
public:
    OpenPoseReArranger() = default;
    virtual ~OpenPoseReArranger() override = default;

    virtual Status reArrange(AbstractHuman &human) override;

private:
    virtual void adjustPoints() override;

    virtual void offsetGroups() override;
    virtual void scaleGroups() override;
    virtual void rotateGroups() override;

    virtual void makeGroups(AbstractHuman &human) override;
};

}

#endif // OPENPOSEREARRANGER_H
