#include "AbstractSkeleton.h"

man::AbstractSkeleton::AbstractSkeleton()
{

}

man::AbstractSkeleton::~AbstractSkeleton()
{
    QMap<QString, AbstractBone*>::iterator i;
    for (i = bones.begin(); i != bones.end(); i++)
        delete i.value();
    std::cout << "-*-*-*-Delete AbsSkel-*-*-*-" <<  name.toStdString() << std::endl; // NOTE: delete
}

int man::AbstractSkeleton::loadFromJson(const Config &config)
{
    QString pathToEntityRel = config.pathsToSkeletons[this->name];
    QString pathToEntityAbs = config.pathApplication + "/" + pathToEntityRel;

    QFile jsonSkeletonFile(pathToEntityAbs);
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
    QFileInfoList listJsonModels = dirModels.entryInfoList();
    if (listJsonModels.isEmpty()) return statusListIsEmpty;

    // Fill JSON
    for(const auto &jsonModel : listJsonModels){
        QFile jsonBoneFile(jsonModel.absoluteFilePath());
        if (!jsonBoneFile.open(QIODevice::ReadOnly)) return statusBoneNotFound;

        QByteArray jsonBoneData = jsonBoneFile.readAll();
        QJsonDocument jsonBoneDocument(QJsonDocument::fromJson(jsonBoneData));
        QJsonObject jsonBoneObject = jsonBoneDocument.object();
        QString boneName = jsonBoneObject.value(jsonFieldName).toString();

        CyberBone* cyberBone = new CyberBone(boneName, dirModels.path());
        cyberBone->boneJsonObject = jsonBoneObject;
        bones.insert(boneName, cyberBone);
    }

    return statusOk;
}

int man::AbstractSkeleton::construct()
{
    int resultConstruct = statusNotFinished;

    QMap<QString, AbstractBone*>::iterator i;
    for (i = bones.begin(); i != bones.end(); i++){
        i.value()->fillProperties();
        i.value()->defineChildren();
        i.value()->defineParents();
        i.value()->calcNewBasePoint();
    }

    isConstructDone = (resultConstruct == statusOk);
    return resultConstruct;
}
