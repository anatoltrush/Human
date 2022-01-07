#include "Human.h"

man::Human::Human()
{
    skeleton = new HumanSkeleton();
}

QMap<QString, QVariant> man::Human::getPropertyList() const
{
    QMap<QString, QVariant> props = AbstractHuman::getPropertyList();
    props["sep"] = "-";
    props["name"] = skeleton->name;
    return props;
}
