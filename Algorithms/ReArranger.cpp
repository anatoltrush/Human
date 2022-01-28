#include "ReArranger.h"

man::ReArranger::ReArranger(){}

man::Status man::ReArranger::reArrange(const man::AbstractHuman &native, man::AbstractHuman &cyber)
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
                if(cyber.skeleton->bones.find(nativeChild->name) != cyber.skeleton->bones.end()){
                    AbstractBone* cyberChild = cyber.skeleton->bones[nativeChild->name];
                    if(cyberChild){
                        offsetBone(nativeChild, cyberChild);
                        scaleBone(nativeChild, cyberChild);
                        stretchBone(nativeChild, cyberChild);
                        rotateBone(nativeChild, cyberChild);
                    }
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

void man::ReArranger::offsetBone(AbstractBone *native, AbstractBone *cyber)
{
    QVector3D diffDist = cyber->basePoint - native->basePoint;
    // --- base pt ---
    cyber->basePoint -= diffDist;
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
}

void man::ReArranger::scaleBone(man::AbstractBone *native, man::AbstractBone *cyber)
{
    for(auto it = native->childrenPoints.begin(); it != native->childrenPoints.end(); it++){
        if(cyber->childrenPoints.find(it.key()) != cyber->childrenPoints.end()){
            float distNative = native->basePoint.distanceToPoint(it.value());
            float distCyber = cyber->basePoint.distanceToPoint(cyber->childrenPoints[it.key()]);
            float koeff = distNative / distCyber;
            // --- chl pts ---
            for(auto& chlPt : cyber->childrenPoints)
                chlPt = QVector3D((chlPt - cyber->basePoint) * koeff + cyber->basePoint);
            // --- stl ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &vr : tri.vertex)
                    vr = QVector3D((vr - cyber->basePoint) * koeff + cyber->basePoint);
        }
        else{} // return?
    }
}

void man::ReArranger::stretchBone(man::AbstractBone *native, man::AbstractBone *cyber)
{
// TODO: IMPLEMENT 1 man::ReArranger::stretchBone
}

void man::ReArranger::rotateBone(man::AbstractBone *native, man::AbstractBone *cyber)
{
    for(auto it = native->childrenPoints.begin(); it != native->childrenPoints.end(); it++){
        if(cyber->childrenPoints.find(it.key()) != cyber->childrenPoints.end()){
            QVector3D diff3D = native->rotationCurrent - cyber->rotationCurrent;            Angle diffAngle(diff3D.x(), diff3D.y(), diff3D.z());
            // --- stl ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &vr : tri.vertex){
                    float zRad = DEG_TO_RAD(-cyber->rotationCurrent.z());
                    vr = rotatePoint3F(vr, Angle(0.0f, 0.0f, zRad), cyber->basePoint);

                    float yRad = DEG_TO_RAD(-cyber->rotationCurrent.y());
                    vr = rotatePoint3F(vr, Angle(0.0f, yRad, 0.0f), cyber->basePoint);

                    float xRad = DEG_TO_RAD(-cyber->rotationCurrent.x());
                    vr = rotatePoint3F(vr, Angle(xRad, 0.0f, 0.0f), cyber->basePoint);

                    vr = rotatePoint3F(vr, native->rotationCurrent.degToRad(), cyber->basePoint);
                }
            // --- chl pts ---
            for(auto& chlPt : cyber->childrenPoints){
                float zRad = DEG_TO_RAD(-cyber->rotationCurrent.z());
                chlPt = rotatePoint3F(chlPt, Angle(0.0f, 0.0f, zRad), cyber->basePoint);

                float yRad = DEG_TO_RAD(-cyber->rotationCurrent.y());
                chlPt = rotatePoint3F(chlPt, Angle(0.0f, yRad, 0.0f), cyber->basePoint);

                float xRad = DEG_TO_RAD(-cyber->rotationCurrent.x());
                chlPt = rotatePoint3F(chlPt, Angle(xRad, 0.0f, 0.0f), cyber->basePoint);

                chlPt = rotatePoint3F(chlPt, native->rotationCurrent.degToRad(), cyber->basePoint);
            }
        }
        else{} // return?

        cyber->rotationCurrent = native->rotationCurrent;
    }
}
