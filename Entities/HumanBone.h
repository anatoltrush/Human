#ifndef HUMANBONE_H
#define HUMANBONE_H

#include "AbstractBone.h"

namespace man{

class HumanBone : public AbstractBone
{
public:
    HumanBone();
    HumanBone(const QString & name, const QString &pathRel);

    QMap<QString, QVariant> getPropertyList() const override;

    virtual void serialize() override;
};

}

#endif // HUMANBONE_H
