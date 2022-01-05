#ifndef HUMANSKELETON_H
#define HUMANSKELETON_H

#include "HumanBone.h"
#include "AbstractSkeleton.h"

namespace man{

class HumanSkeleton : public AbstractSkeleton, public IProperty
{
public:
    HumanSkeleton();

    virtual QMap<QString, QVariant> getPropertyList() const override;
};

}

#endif // HUMANSKELETON_H
