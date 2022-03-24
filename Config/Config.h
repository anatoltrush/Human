#ifndef CONFIG_H
#define CONFIG_H

#include "ConfigDefines.h"

namespace man{

enum Source{ERR, File, DB, URL};

class Config
{
public:
    Config();
    ~Config();

    int testValue = -1;

    // Common settings
    Source source = Source::ERR;
    QString loadFrom;
    QString pathApplication;
    QString pathSettingsFile;

    QJsonObject settingsJsonObject;

    // Entities settings
    QString pathEntities;

    QJsonObject entitiesJsonObject;
    QMap<QString, QString>pathsToSkeletons; // entity name / entity path

    Status loadSettings();
    Status saveSettings();
};

}

#endif // CONFIG_H
