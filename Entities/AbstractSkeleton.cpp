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

man::Status man::AbstractSkeleton::loadFromJson(const Config &config, bool isHuman)
{
    QString pathToEntityRel = config.pathsToSkeletons[this->name];
    QString pathToEntityAbs = config.pathApplication + "/" + pathToEntityRel;
    pathToEntityAbs.replace("\\", "/");

    QFile jsonSkeletonFile(pathToEntityAbs);
    if (!jsonSkeletonFile.open(QIODevice::ReadOnly)) return StatusFileNotFound;

    QByteArray jsonSkeletonData = jsonSkeletonFile.readAll();
    QJsonDocument jsonSkeletonDocument(QJsonDocument::fromJson(jsonSkeletonData));
    QJsonObject jsonSkeletonObject = jsonSkeletonDocument.object();

    // LOAD JSONS BONES
    QString pathToModelsRel = jsonSkeletonObject[jsonFolderPathModels].toString();
    if(pathToModelsRel.isEmpty()) return StatusPathIsEmpty;
    QString pathToModelsDirAbs = QCoreApplication::applicationDirPath() + "/" + pathToModelsRel;
    pathToModelsDirAbs.replace("\\", "/");

    // DIR
    QDir dirModels(pathToModelsDirAbs);
    if (!dirModels.exists()) return StatusDirNotFound;
    if (dirModels.isEmpty()) return StatusDirIsEmpty;
    QStringList filters;
    filters << "*.json" << "*.JSON";
    dirModels.setNameFilters(filters);
    QFileInfoList listJsonModels = dirModels.entryInfoList();
    if (listJsonModels.isEmpty()) return StatusJsonListIsEmpty;

    // Fill JSON
    for(const auto &jsonModel : listJsonModels){
        QFile jsonBoneFile(jsonModel.absoluteFilePath());
        if (!jsonBoneFile.open(QIODevice::ReadOnly))
            return StatusBoneNotLoaded;

        QByteArray jsonBoneData = jsonBoneFile.readAll();
        QJsonDocument jsonBoneDocument(QJsonDocument::fromJson(jsonBoneData));
        QJsonObject jsonBoneObject = jsonBoneDocument.object();
        QString boneName = jsonBoneObject.value(jsonFieldName).toString();

        AbstractBone* abstractBone;
        if(isHuman)
            abstractBone = new HumanBone(boneName, dirModels.path());
        else
            abstractBone = new CyberBone(boneName, dirModels.path());
        abstractBone->boneJsonObject = jsonBoneObject;
        bones.insert(boneName, abstractBone);
    }

    return StatusOk;
}

man::Status man::AbstractSkeleton::construct()
{
    if(bones.isEmpty()) return StatusBonesListIsEmpty;
    // -----
    QMap<QString, AbstractBone*>::iterator i;
    for (i = bones.begin(); i != bones.end(); i++){
        i.value()->fillProperties();
        int res3DLoad = stlReader.parseFromFile(i.value()->pathTo3DModelAbs, i.value()->stlObject);
        stlReader.calcAddProps(i.value()->stlObject);
    }

    // --- ChildrenPointers ---
    QMap<QString, AbstractBone*>::iterator bnIter;
    for (bnIter = bones.begin(); bnIter != bones.end(); bnIter++){
        QMap<QString, Point3F>::iterator chldIter;
        for(chldIter = bnIter.value()->childrenPoints.begin(); chldIter != bnIter.value()->childrenPoints.end(); chldIter++){
            QString childName = chldIter.key();
            QMap<QString, AbstractBone*>::iterator mapFind = bones.find(childName);
            if(mapFind != bones.end()){
                bnIter.value()->childrenPointers.push_back(bones[childName]);
                bones[childName]->parentsPointers.push_back(bnIter.value());
            }
        }
    }

    // --- BasePoints ---
    AbstractBone* startBone = nullptr;
    QMap<QString, AbstractBone*>::iterator startIter;
    for (startIter = bones.begin(); startIter != bones.end(); startIter++)
        if(startIter.value()->parentName == notAvlbl)
            startBone = startIter.value();
    if(!startBone){
        return StatusBoneNotFound;
    }
    else{
        startBone->applyOffsets(startBone->parentOffsetPoint);
    }

    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                thisChild->basePoint = &vecParents[i]->childrenPoints[thisChild->name];
                Point3F fullOffSet = *thisChild->basePoint + thisChild->parentOffsetPoint;
                thisChild->applyOffsets(fullOffSet);
                // ---
                vecChildren.push_back(thisChild);
            }
        // -----
        if(vecChildren.empty()) break;
        vecParents = vecChildren;
    }
    // i.value()->applyRotation(); // 1

    isConstructDone = true;
    return StatusOk;
}
