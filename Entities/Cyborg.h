#ifndef CYBORG_H
#define CYBORG_H

#include "CyberSkeleton.h"
#include "AbstractHuman.h"

namespace man{

class Cyborg : public AbstractHuman, public IProperty
{
public:
    Cyborg();

    virtual QMap<QString, QVariant> getPropertyList() const override;

};

}

#endif // CYBORG_H
