#ifndef MEDIAPIPEREARRANGER_H
#define MEDIAPIPEREARRANGER_H

#include "Algorithms/AbstractReArranger.h"

namespace man{

class MediaPipeReArranger : public AbstractReArranger
{
public:
    MediaPipeReArranger() = default;
    virtual ~MediaPipeReArranger() override = default;

    virtual Status reArrange(AbstractHuman &human) override;

protected:
    virtual void adjustPoints() override;

    virtual void offsetGroups() override;
    virtual void scaleGroups() override;
    virtual void rotateGroups() override;
};

}

#endif // MEDIAPIPEREARRANGER_H
