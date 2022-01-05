#ifndef CYBERBONE_H
#define CYBERBONE_H

#include "AbstractBone.h"
#include "Interfaces/IProperty.h"

namespace man{

class CyberBone : public AbstractBone, public IProperty
{
public:
    CyberBone();
    CyberBone(const QString &name, const QString &pathRel);

    QMap<QString, QVariant> getPropertyList() const override;

    virtual void serialize() override;
};

}

#endif // CYBERBONE_H
