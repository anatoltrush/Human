#include "CyberSkeleton.h"

man::CyberSkeleton::CyberSkeleton()
{
    name = cyberSkeleton;
    isHuman = false;
}

QMap<QString, QVariant> man::CyberSkeleton::getPropertyList() const
{
    QMap<QString, QVariant> props;
    props["CyberSkeleton"] = "<-CyberSkeleton->";
    return props;
}

