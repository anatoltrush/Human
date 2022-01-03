#ifndef CONFIG_H
#define CONFIG_H

#include "ConfigDefines.h"

namespace man{

class Config
{
public:
    Config();

    QString pathApplication;

    QJsonObject configJsonObject;

    QMap<QString, QString>pathsToSkeletons; // entity name / entity path

    Status loadConfigData();
};

}

#endif // CONFIG_H
