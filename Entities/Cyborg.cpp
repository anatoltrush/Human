#include "Cyborg.h"

man::Cyborg::Cyborg()
{
    skeleton = new CyberSkeleton();
}

QMap<QString, QVariant> man::Cyborg::getPropertyList() const
{
    QMap<QString, QVariant> props = AbstractHuman::getPropertyList();
    props["sep"] = "-";
    props["name"] = skeleton->name;
    return props;
}
