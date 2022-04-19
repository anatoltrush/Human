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

protected:
    virtual void adjustPoints() override;

    virtual void offsetGroups() override;
    virtual void scaleGroups() override;
    virtual void rotateGroups() override;
};

}

#endif // OPENPOSEREARRANGER_H
