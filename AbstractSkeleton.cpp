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
    if (listJsonModels.isEmpty()) return statusJsonListIsEmpty;

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
    if(bones.isEmpty()) return statusBonesListIsEmpty;
    // -----
    QMap<QString, AbstractBone*>::iterator i;
    for (i = bones.begin(); i != bones.end(); i++){
        i.value()->fillProperties();
        i.value()->load3DModels();
        i.value()->applyOffsets();
    }

    // ChildrenPts
    QMap<QString, AbstractBone*>::iterator b;
    for (b = bones.begin(); b != bones.end(); b++){
        for(size_t is = 0; is < b.value()->childrenStr.size(); is++){
            QString childName = b.value()->childrenStr[is];
            /*AbstractBone* childPtr = bones[childName]; // Version with null pointers
            b.value()->childrenPtr.push_back(bones[childName]);
            if(childPtr)
                bones[childName]->parentsPtr.push_back(b.value());*/
            QMap<QString, AbstractBone*>::iterator mapFind = bones.find(childName);
            if(mapFind != bones.end()){
                b.value()->childrenPtr.push_back(bones[childName]);
                bones[childName]->parentsPtr.push_back(b.value());
            }
        }
    }
    isConstructDone = true;
    return statusOk;
}
