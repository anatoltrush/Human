#ifndef IPROPERTY_H
#define IPROPERTY_H

#include <QMap>

namespace man{

class IProperty
{
public:
    IProperty() = default;
    virtual ~IProperty() = default;

    virtual QMap<QString, QVariant> getPropertyList() const = 0;
};

}

#endif // IPROPERTY_H
