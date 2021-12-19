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

    std::map<QString, QString>pathsSkeleton;

    int loadConfigData();
};

}

#endif // CONFIG_H
