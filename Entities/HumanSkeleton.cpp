#include "HumanSkeleton.h"

man::HumanSkeleton::HumanSkeleton()
{
    name = humanSkeleton;
    isHuman = true;
}

QMap<QString, QVariant> man::HumanSkeleton::getPropertyList() const
{
    QMap<QString, QVariant> props;
    props["HumanSkeleton"] = "<-HumanSkeleton->";
    return props;
}
