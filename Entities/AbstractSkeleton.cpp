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
    QJsonParseError jsonParserSkel;
    QJsonDocument jsonSkeletonDocument(QJsonDocument::fromJson(jsonSkeletonData, &jsonParserSkel));
    if(jsonParserSkel.error != QJsonParseError::NoError)
        return StatusBadFileFormat;
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
        QJsonParseError jsonParserBone;
        QJsonDocument jsonBoneDocument(QJsonDocument::fromJson(jsonBoneData, &jsonParserBone));
        if(jsonParserBone.error != QJsonParseError::NoError)
            return StatusBadFileFormat;
        QJsonObject jsonBoneObject = jsonBoneDocument.object();
        QString boneName = jsonBoneObject.value(jsonFieldName).toString();

        AbstractBone* abstractBone;
        if(this->isHuman)
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
        if(startIter.value()->parentOffset.str == notAvlbl)
            startBone = startIter.value();
    if(!startBone){
        return StatusBoneNotFound;
    }
    else{
        startBone->applyOffsets(startBone->parentOffset.toPoint3F());
    }

    // --- Apply offsets ---
    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                thisChild->basePoint = &vecParents[i]->childrenPoints[thisChild->name];
                Point3F fullOffSet = *thisChild->basePoint + thisChild->parentOffset.toPoint3F();
                thisChild->applyOffsets(fullOffSet);
                // ---
                vecChildren.push_back(thisChild);
            }
        // -----
        if(vecChildren.empty()) break;
        vecParents = vecChildren;
    }
    // --- Height ---
    calcHeight();

    // --- Apply rotation ---    
    rotateBonesAll(startBone);

    // --- Reset bones ---
    resetBones();

    isConstructDone = true;
    return StatusOk;
}

void man::AbstractSkeleton::rotateBonesAll(AbstractBone *startBone)
{
    startBone->rotateBone(startBone->childrenPoints.begin().value(), startBone->rotation);
    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                rotateBonesSingle(thisChild, thisChild->rotation);
                vecChildren.push_back(thisChild);
            }
        // -----
        if(vecChildren.empty()) break;
        vecParents = vecChildren;
    }
}

void man::AbstractSkeleton::rotateBonesSingle(AbstractBone *startBone, const Angle &angles)
{
    startBone->rotation = angles;
    // ---
    std::vector<AbstractBone*> allChildBones = {startBone};
    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                allChildBones.push_back(thisChild);
                // ---
                vecChildren.push_back(thisChild);
            }
        // -----
        if(vecChildren.empty()) break;
        vecParents = vecChildren;
    }
    // ---
    for(const auto &bn : allChildBones)
        bn->rotateBone(*startBone->basePoint, angles);
}

QMap<QString, QVariant> man::AbstractSkeleton::getPropertyList() const
{

}

void man::AbstractSkeleton::resetBones()
{
    for(const auto &bn : qAsConst(bones)){
        bn->isExist = this->isHuman;
        bn->interSects.clear();
        for(auto &tr : bn->stlObject.triangles)
            tr.isGood = this->isHuman;
    }
}

void man::AbstractSkeleton::calcHeight()
{
    Point3F highestPt;
    Point3F lowestPt;
    for(const auto &bn : qAsConst(bones)){
        Point3F hPt = bn->getHighestPoint();
        if(hPt.z > highestPt.z) highestPt = hPt;
        // ---
        Point3F lPt = bn->getLowestPoint();
        if(lPt.z < lowestPt.z) lowestPt = lPt;
    }
    this->height = highestPt.z - lowestPt.z;
}
