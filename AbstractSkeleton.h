#ifndef ABSTRACTSKELETON_H
#define ABSTRACTSKELETON_H

#include <QString>

#include "ConfigDefines.h"

namespace man{

class AbstractSkeleton
{
public:
    AbstractSkeleton();
    virtual ~AbstractSkeleton();

    QString name;
    QFileInfoList listJsonModels;

    virtual int loadFromJson(QString &pathToJson);
};

}

#endif // ABSTRACTSKELETON_H
