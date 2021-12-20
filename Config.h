#ifndef CONFIG_H
#define CONFIG_H

#include "ConfigDefines.h"

#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCoreApplication>

namespace man{

class Config
{
public:
    Config();

    QString pathApplication;

    QJsonObject configJsonObject;

    QMap<QString, QString>pathsToEntities; // entity name / entity path

    int loadConfigData();
};

}

#endif // CONFIG_H
