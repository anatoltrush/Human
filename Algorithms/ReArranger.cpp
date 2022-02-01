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
                        stretchAndRotateBone(nativeChild, cyberChild);
                        //scaleBone(nativeChild, cyberChild);
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

void man::ReArranger::stretchAndRotateBone(man::AbstractBone *native, man::AbstractBone *cyber)
{
    //if(cyber->name != "LeftLeg") return;
    for(auto it = native->childrenPoints.begin(); it != native->childrenPoints.end(); it++){
        if(cyber->childrenPoints.find(it.key()) != cyber->childrenPoints.end()){
            QVector3D* chldPt = &cyber->childrenPoints[it.key()];
            //*chldPt = rotatePoint3FBack(*chldPt, cyber->rotationCurrent.degToRad(), cyber->basePoint);

            //Angle frarm = angle3Pts0_180Reverse(*chldPt, cyber->basePoint);

            //*chldPt = rotatePoint3FBack(*chldPt, frarm.degToRad(), cyber->basePoint);
            //QVector3D falseNatChld = it.value();
            //falseNatChld = rotatePoint3FBack(falseNatChld, native->rotationCurrent, native->basePoint);
            // --- calc koeffs ---
            float distXCyb = chldPt->x() - cyber->basePoint.x();
            float distYCyb = chldPt->y() - cyber->basePoint.y();
            float distZCyb = chldPt->z() - cyber->basePoint.z();
            /*float distXNat = falseNatChld.x() - native->basePoint.x();
            float distYNat = falseNatChld.y() - native->basePoint.y();
            float distZNat = falseNatChld.z() - native->basePoint.z();*/
            //QVector3D koeffs(distXNat / distXCyb, distYNat / distYCyb, distZNat / distZCyb);
            // --- apply koeffs ---
            //*chldPt = (*chldPt - cyber->basePoint) * koeffs + cyber->basePoint;
            // ---
            //*chldPt = rotatePoint3F(*chldPt, native->rotationCurrent.degToRad(), cyber->basePoint);

            // --- stl ---
            /*for(auto& tri : cyber->stlObject.triangles)
                for(auto &vr : tri.vertex){
                    float zRad = DEG_TO_RAD(-cyber->rotationCurrent.z());
                    vr = rotatePoint3F(vr, Angle(0.0f, 0.0f, zRad), cyber->basePoint);
                    float yRad = DEG_TO_RAD(-cyber->rotationCurrent.y());
                    vr = rotatePoint3F(vr, Angle(0.0f, yRad, 0.0f), cyber->basePoint);
                    float xRad = DEG_TO_RAD(-cyber->rotationCurrent.x());
                    vr = rotatePoint3F(vr, Angle(xRad, 0.0f, 0.0f), cyber->basePoint);
                    // --- apply koeffs ---
                    // ---
                    vr = rotatePoint3F(vr, native->rotationCurrent.degToRad(), cyber->basePoint);
                }*/
        }
        else{} // return?

        //cyber->rotationCurrent = native->rotationCurrent;
    }
}
