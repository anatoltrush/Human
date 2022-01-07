#include "AbstractHuman.h"

man::AbstractHuman::AbstractHuman()
{

}

man::AbstractHuman::~AbstractHuman()
{    
    delete skeleton;
    std::cout << "-XXX-Delete AbsHum-XXX-" << std::endl; // NOTE: delete
}

QMap<QString, QVariant> man::AbstractHuman::getPropertyList() const
{
    QMap<QString, QVariant> props;
    props["heigh"] = skeleton->height;
    return props;
}
