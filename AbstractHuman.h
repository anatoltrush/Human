#ifndef ABSTRACTHUMAN_H
#define ABSTRACTHUMAN_H

#include <QUuid>
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

    QString uuid = QUuid::createUuid().toString();
    QString firstName; // name
    QString lastName; // family
    QDateTime birth;

};

}

#endif // ABSTRACTHUMAN_H
