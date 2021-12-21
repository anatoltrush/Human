#include "AbstractSkeleton.h"

man::AbstractSkeleton::AbstractSkeleton()
{

}

man::AbstractSkeleton::~AbstractSkeleton()
{

}

int man::AbstractSkeleton::loadFromJson(QString &pathToJson)
{
    QFile jsonSkeletonFile(pathToJson);
    if (!jsonSkeletonFile.open(QIODevice::ReadOnly)) return statusFileNotFound;

    QByteArray jsonSkeletonData = jsonSkeletonFile.readAll();
    QJsonDocument jsonSkeletonDocument(QJsonDocument::fromJson(jsonSkeletonData));
    QJsonObject jsonSkeletonObject = jsonSkeletonDocument.object();

    // LOAD JSONS BONES
    QString pathToModelsRel = jsonSkeletonObject[jsonFolderPathModels].toString();
    if(pathToModelsRel.isEmpty()) return statusPathIsEmpty;
    QString pathToModelsDirAbs = QCoreApplication::applicationDirPath() + "/" + pathToModelsRel;

    // DIR
    QDir dirModels(pathToModelsDirAbs);
    if (!dirModels.exists()) return statusDirNotFound;
    if (dirModels.isEmpty()) return statusDirIsEmpty;
    QStringList filters;
    filters << "*.json" ;
    dirModels.setNameFilters(filters);
    listJsonModels = dirModels.entryInfoList();
    if (listJsonModels.isEmpty()) return statusListIsEmpty;

    // 3D
    for(const auto &jsonModel : listJsonModels){

    }

    return statusOk;
}
