#ifndef HUMAN_H
#define HUMAN_H

#include "AbstractHuman.h"
#include "HumanSkeleton.h"
#include "PersonalInfo.h"

namespace man{

class Human : public AbstractHuman
{
public:
    Human();

    PersonalInfo personalInfo;

    virtual QMap<QString, QVariant> getPropertyList() const override;
};

}

#endif // HUMAN_H
