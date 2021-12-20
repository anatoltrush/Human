#include "AbstractHuman.h"

man::AbstractHuman::AbstractHuman()
{

}

int man::AbstractHuman::loadEntityData(const Config &config, const QString &name)
{
    QString pathToEntityRel = config.pathsToEntities[name];
    QString pathToEntityAbs = config.pathApplication + "/" + pathToEntityRel;

    QFile jsonEntityFile(pathToEntityAbs);
    if (!jsonEntityFile.open(QIODevice::ReadOnly))
        return Status::statusFileNotFound;

    QByteArray jsonEntityData = jsonEntityFile.readAll();
    QJsonDocument jsonEntityDocument(QJsonDocument::fromJson(jsonEntityData));
    QJsonObject jsonEntityObject = jsonEntityDocument.object();
    jsonEntities.push_back(jsonEntityObject);

    return 0;
}
