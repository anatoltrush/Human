#include "ReArranger.h"

man::ReArranger::ReArranger()
{

}

man::Status man::ReArranger::reArrange(const man::AbstractHuman &native, man::AbstractHuman &cyber)
{
    Status resDists = reArrangeDistances(native, cyber);
    if(resDists == StatusOk){
        Status resAngles = reArrangeAngle(native, cyber);
        return resAngles;
    }
    else return resDists;
}

man::Status man::ReArranger::reArrangeDistances(const man::AbstractHuman &native, man::AbstractHuman &cyber)
{
    AbstractBone* startBoneCyber = cyber.skeleton->getStartBone();
    AbstractBone* startBoneNative = native.skeleton->getStartBone();
    if(!startBoneCyber || !startBoneNative) return StatusBoneNotFound;

    std::vector<AbstractBone*> vecParents = {startBoneNative};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* nativeChild = vecParents[i]->childrenPointers[j];
                // make smthng
                QMap<QString, AbstractBone*>::iterator mapFind = cyber.skeleton->bones.find(nativeChild->name);
                if(mapFind != cyber.skeleton->bones.end()){
                    AbstractBone* cyberChild = cyber.skeleton->bones[nativeChild->name];
                    moveAndStretch(nativeChild, cyberChild);
                }
                // ---
                vecChildren.push_back(nativeChild);
            }
        // -----
        if(vecChildren.empty()) break;
        vecParents = vecChildren;
    }

    return StatusOk;
}

man::Status man::ReArranger::reArrangeAngle(const man::AbstractHuman &native, man::AbstractHuman &cyber)
{
    // TODO: implement
    return StatusOk;
}

void man::ReArranger::moveAndStretch(AbstractBone *native, AbstractBone *cyber)
{ // need to move all down
    /*alg
     * -
     * /

    // --- MOVE ---
    QVector3D diffDist = *cyber->basePoint - *native->basePoint;
    // --- base pt ---
    *cyber->basePoint -= diffDist;
    // --- chl pts ---
    for(auto& chlPt : cyber->childrenPoints)
        chlPt -= diffDist;
    // --- stl ---
    for(auto& tri : cyber->stlObject.triangles)
        for(auto &vr : tri.vertex)
            vr -= diffDist;
    for(auto& addTri : cyber->stlObject.additional)
        for(auto &vr : addTri.vertex)
            vr -= diffDist;

    // --- STRETCH ---
    for(auto it = native->childrenPoints.begin(); it!=native->childrenPoints.end(); it++){
        QMap<QString, QVector3D>::iterator mapFindChPt = cyber->childrenPoints.find(it.key());
        if(mapFindChPt != cyber->childrenPoints.end()){
            float distNative = native->basePoint->distanceToPoint(it.value());
            float distCyber = cyber->basePoint->distanceToPoint(cyber->childrenPoints[it.key()]);
            float koeff = distNative / distCyber;
            QVector3D fullCybOffset = *cyber->basePoint + cyber->parentOffset;
            // --- stl ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &vr : tri.vertex)
                    vr = QVector3D((vr - fullCybOffset) * koeff + fullCybOffset);
            // --- chl pts ---
            for(auto& chlPt : cyber->childrenPoints)
                chlPt = QVector3D((chlPt - fullCybOffset) * koeff + fullCybOffset); // ???
        }
        else{/*maybe return*/}
    }
}
