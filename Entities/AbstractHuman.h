#ifndef ABSTRACTHUMAN_H
#define ABSTRACTHUMAN_H

#include <QUuid>

#include "AbstractSkeleton.h"

namespace man{

class AbstractHuman : public IProperty
{
public:
    AbstractHuman();
    virtual ~AbstractHuman();

    AbstractSkeleton* skeleton = nullptr;

    QString uuid = QUuid::createUuid().toString();

    virtual QMap<QString, QVariant> getPropertyList() const override;

};

}

#endif // ABSTRACTHUMAN_H
