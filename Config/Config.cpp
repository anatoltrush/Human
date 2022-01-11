#include "Config.h"

man::Config::Config()
{
    pathApplication = QCoreApplication::applicationDirPath();    
}

man::Status man::Config::loadConfigData()
{
    QString pathConfigFile = pathApplication + "/" + fileConfig;

    QFile jsonConfigFile(pathConfigFile);
    if (!jsonConfigFile.open(QIODevice::ReadOnly))
        return StatusFileNotFound;

    QByteArray jsonConfigData = jsonConfigFile.readAll();
    QJsonParseError jsonParser;
    QJsonDocument jsonConfigDocument(QJsonDocument::fromJson(jsonConfigData, &jsonParser));
    if(jsonParser.error != QJsonParseError::NoError)
        return StatusBadFileFormat;
    configJsonObject = jsonConfigDocument.object();

    QJsonArray skeletonArray = configJsonObject[jsonFieldSkeletons].toArray();
    for(const auto &skelPths : qAsConst(skeletonArray)){
        QString name = skelPths.toObject().value(jsonFieldName).toString();
        QString path = skelPths.toObject().value(jsonFieldPath).toString();
        pathsToSkeletons.insert(name, path);
    }
    return StatusOk;
}
