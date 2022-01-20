#include "AbstractSkeleton.h"

man::AbstractSkeleton::AbstractSkeleton()
{

}

man::AbstractSkeleton::~AbstractSkeleton()
{
    for (auto i = bones.begin(); i != bones.end(); i++)
        delete i.value();
    std::cout << "-*-*-*-Delete AbsSkel-*-*-*-" <<  name.toStdString() << std::endl; // NOTE: delete
}

man::Status man::AbstractSkeleton::loadFromJson(const Config &config)
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
    for(const auto &jsonModel : qAsConst(listJsonModels)){
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
    for (auto i = bones.begin(); i != bones.end(); i++){
        i.value()->fillProperties();
        int res3DLoad = stlHandler.parseFromFile(i.value()->pathTo3DModelAbs, i.value()->stlObject);
        stlHandler.calcAddProperties(i.value()->stlObject);
    }

    // --- ChildrenPointers ---
    for(auto bnI = bones.begin(); bnI != bones.end(); bnI++){
        for(auto chldI = bnI.value()->childrenPoints.begin(); chldI != bnI.value()->childrenPoints.end(); chldI++){
            QString childName = chldI.key();
            if(bones.find(childName) != bones.end()){
                bnI.value()->childrenPointers.push_back(bones[childName]);
                bones[childName]->parentPointer = bnI.value();
            }
        }
    }

    // --- BasePoints ---
    AbstractBone* startBone = getStartBone();
    if(!startBone)
        return StatusBoneNotFound;
    else
        startBone->applyOffsets(startBone->parentOffset.toPoint3F());

    // --- Apply offsets ---
    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                thisChild->basePoint = &vecParents[i]->childrenPoints[thisChild->name];
                QVector3D fullOffSet = *thisChild->basePoint + thisChild->parentOffset.toPoint3F();
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

man::AbstractBone *man::AbstractSkeleton::getStartBone()
{
    AbstractBone* startBone = nullptr;
    for (auto i = bones.begin(); i != bones.end(); i++){
        if(!i.value()) continue;
        if(i.value()->parentOffset.str == notAvlbl)
            startBone = i.value();
    }
    return startBone;
}

void man::AbstractSkeleton::rotateBonesAll(AbstractBone *startBone)
{
    if(!startBone) return;
    // ---
    startBone->rotateBone(startBone->childrenPoints.begin().value(), startBone->rotation);
    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                // make smthng
                rotateBonesSingle(thisChild, thisChild->rotation);
                // ---
                vecChildren.push_back(thisChild);
            }
        // -----
        if(vecChildren.empty()) break;
        vecParents = vecChildren;
    }
}

void man::AbstractSkeleton::rotateBonesSingle(AbstractBone *startBone, const Angle &angles)
{
    if(!startBone) return;
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
        if(!bn) continue;
        bn->isExist = this->isHuman;
        bn->intersections.clear();
        for(auto &tr : bn->stlObject.triangles)
            tr.isGood = this->isHuman;
        bn->stlObject.additional.clear();
    }
}

man::Status man::AbstractSkeleton::serialize(const QString &pathDir)
{
    for (auto i = bones.begin(); i != bones.end(); i++){
        if(!i.value()) continue;
        if(i.value()->isExist){
            StlObject object; // temporary obj
            std::vector<Triangle> allTriangles;
            // ---
            for(const auto &tr : i.value()->stlObject.triangles){
                if(tr.isGood)
                    allTriangles.push_back(tr);
            }
            for(const auto &ad : i.value()->stlObject.additional){
                if(ad.isGood)
                    allTriangles.push_back(ad);
            }
            // ---
            object.triangles = allTriangles;
            if(i.key().isEmpty())
                object.objectName = QUuid::createUuid().toString();
            else
                object.objectName = i.key();

            // --- stlHandler ---
            Status res = stlHandler.saveToFile(pathDir, object);
            if(res != StatusOk) return res;
        }
    }
    return StatusOk;
}

void man::AbstractSkeleton::calcHeight()
{
    QVector3D highestPt;
    QVector3D lowestPt;
    for(const auto &bn : qAsConst(bones)){
        QVector3D hPt = bn->getHighestPoint();
        if(hPt.z() > highestPt.z()) highestPt = hPt;
        // ---
        QVector3D lPt = bn->getLowestPoint();
        if(lPt.z() < lowestPt.z()) lowestPt = lPt;
    }
    this->height = highestPt.z() - lowestPt.z();
}
