#include "Config.h"

man::Config::Config()
{
    pathApplication = QCoreApplication::applicationDirPath();    
    pathSettingsFile = pathApplication + "/" + fileSettings;
}

man::Config::~Config()
{
    saveSettings();
}

man::Status man::Config::loadSettings()
{
    QFile jsonEntitiesFile(pathSettingsFile);
    if (!jsonEntitiesFile.open(QIODevice::ReadOnly))
        return StatusFileNotFound;

    QByteArray jsonSettingsData = jsonEntitiesFile.readAll();
    QJsonParseError jsonSettingsParser;
    QJsonDocument jsonSettingsDocument(QJsonDocument::fromJson(jsonSettingsData, &jsonSettingsParser));
    if(jsonSettingsParser.error != QJsonParseError::NoError)
        return StatusBadFileFormat;
    settingsJsonObject = jsonSettingsDocument.object();

    // ---
    pathEntities = settingsJsonObject[jsonFieldEntities].toString();
    loadFrom = settingsJsonObject[jsonFieldLoadFrom].toString();
    // ---
    testValue = settingsJsonObject["testValue"].toInt();
    testValue++;
    // ---
    if(loadFrom == "File") source = Source::File;
    if(loadFrom == "DB") source = Source::DB;
    if(loadFrom == "URL") source = Source::URL;
    if(source == Source::ERR) return StatusBadData;
    // ---

    // --- load entities ---
    if(source == Source::File){
        QString pathAbsEntities = pathApplication + "/" + pathEntities + "/" + fileEntities;
        QFile jsonEntitiesFile(pathAbsEntities);
        if (!jsonEntitiesFile.open(QIODevice::ReadOnly))
            return StatusFileNotFound;

        QByteArray jsonEntitiesData = jsonEntitiesFile.readAll();
        QJsonParseError jsonEntitiesParser;
        QJsonDocument jsonEntitiesDocument(QJsonDocument::fromJson(jsonEntitiesData, &jsonEntitiesParser));
        if(jsonEntitiesParser.error != QJsonParseError::NoError)
            return StatusBadFileFormat;
        entitiesJsonObject = jsonEntitiesDocument.object();

        // ---
        QJsonArray skeletonArray = entitiesJsonObject[jsonFieldSkeletons].toArray();
        for(const auto &skelPths : qAsConst(skeletonArray)){
            QString name = skelPths.toObject().value(jsonFieldName).toString();
            QString path = skelPths.toObject().value(jsonFieldPath).toString();
            pathsToSkeletons.insert(name, path);
        }
        return StatusOk;
    }
    else if(source == Source::DB) return StatusOk;
    else if(source == Source::URL) return StatusOk;
    else return StatusBadData;
}

man::Status man::Config::saveSettings()
{
    QFile jsonSettingsFile(pathSettingsFile);
    if (!jsonSettingsFile.open(QIODevice::WriteOnly))
        return StatusFileNotFound;

    settingsJsonObject["testValue"] = testValue;

    jsonSettingsFile.write(QJsonDocument(settingsJsonObject).toJson(QJsonDocument::Indented));
    jsonSettingsFile.close();

    return StatusOk;
}
