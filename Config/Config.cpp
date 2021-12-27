#include "Config.h"

man::Config::Config()
{
    pathApplication = QCoreApplication::applicationDirPath();    
}

int man::Config::loadConfigData()
{
    QString pathConfigFile = pathApplication + "/" + fileConfig;

    QFile jsonConfigFile(pathConfigFile);
    if (!jsonConfigFile.open(QIODevice::ReadOnly))
        return statusFileNotFound;

    QByteArray jsonConfigData = jsonConfigFile.readAll();
    QJsonDocument jsonConfigDocument(QJsonDocument::fromJson(jsonConfigData));
    configJsonObject = jsonConfigDocument.object();

    QJsonArray skeletonArray = configJsonObject[jsonFieldSkeletons].toArray();
    for(const auto &skelPths : skeletonArray){
        QString name = skelPths.toObject().value(jsonFieldName).toString();
        QString path = skelPths.toObject().value(jsonFieldPath).toString();
        pathsToSkeletons.insert(name, path);
    }
    return statusOk;
}
