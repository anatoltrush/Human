#ifndef ABSTRACTHUMAN_H
#define ABSTRACTHUMAN_H

#include <QDateTime>

#include "Config.h"
#include "AbstractSkeleton.h"

namespace man{

class AbstractHuman
{
public:
    AbstractHuman();
    virtual ~AbstractHuman();

    AbstractSkeleton* skeleton = nullptr;

    QString firstName; // name
    QString lastName; // family
    QDateTime birth;

};

}

#endif // ABSTRACTHUMAN_H
