#ifndef CYBERSKELETON_H
#define CYBERSKELETON_H

#include "CyberBone.h"
#include "AbstractSkeleton.h"

namespace man{

class CyberSkeleton : public AbstractSkeleton
{
public:
    CyberSkeleton();

    virtual QMap<QString, QVariant> getPropertyList() const override;
};

}

#endif // CYBERSKELETON_H
