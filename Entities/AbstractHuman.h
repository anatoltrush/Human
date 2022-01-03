#ifndef ABSTRACTHUMAN_H
#define ABSTRACTHUMAN_H

#include <QUuid>

#include "Config/Config.h"
#include "AbstractSkeleton.h"

namespace man{

class AbstractHuman
{
public:
    AbstractHuman();
    virtual ~AbstractHuman();

    AbstractSkeleton* skeleton = nullptr;

    QString uuid = QUuid::createUuid().toString();

};

}

#endif // ABSTRACTHUMAN_H
