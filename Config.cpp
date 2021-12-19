#include "Config.h"

man::Config::Config()
{
    pathApplication = QCoreApplication::applicationDirPath();    
}

int man::Config::loadConfigData()
{
    QString pathConfigFile = pathApplication + "/" + fileConfig;

    QFile jsonConfigFile(pathConfigFile);
    if (!jsonConfigFile.open(QIODevice::ReadOnly)) return -1;

    QByteArray jsonConfigData = jsonConfigFile.readAll();
    QJsonDocument jsonConfigDocument(QJsonDocument::fromJson(jsonConfigData));
    configJsonObject = jsonConfigDocument.object();

    QJsonArray skeletonArray = configJsonObject[jsonFieldEntities].toArray();
    for(const auto &skelPths : skeletonArray){
        QString name = skelPths.toObject().value(jsonFieldName).toString();
        QString path = skelPths.toObject().value(jsonFieldPath).toString();
        pathsSkeleton.insert(std::pair<QString, QString>(name, path));
    }
    return 0;
}
