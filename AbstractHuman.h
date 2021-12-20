#ifndef ABSTRACTHUMAN_H
#define ABSTRACTHUMAN_H

#include <vector>

#include <QString>
#include <QDateTime>

#include "Config.h"

namespace man{

class AbstractHuman
{
public:
    AbstractHuman();

    QString firstName; // name
    QString lastName; // family
    QDateTime birth;

    std::vector<QJsonObject>jsonEntities;

    int loadEntityData(const Config& config, const QString& name);

};

}

#endif // ABSTRACTHUMAN_H
