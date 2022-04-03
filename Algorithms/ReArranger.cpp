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
                        //stretchAndRotateBone(nativeChild, cyberChild);
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
    // --- anchor ---
    cyber->anchorDown -= diffDist;
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
    //if(cyber->name != "LeftHand") return;
    for(auto it = native->childrenPoints.begin(); it != native->childrenPoints.end(); it++){
        if(cyber->childrenPoints.find(it.key()) != cyber->childrenPoints.end()){
            QVector3D* chldPt = &cyber->childrenPoints[it.key()];
            *chldPt = rotatePoint3FBack(*chldPt, cyber->rotationCurrent.degToRad(), cyber->basePoint);
            QVector3D falseNatChld = it.value();
            falseNatChld = rotatePoint3FBack(falseNatChld, native->rotationCurrent.degToRad(), native->basePoint);

            // --- calc koeffs ---
            QVector3D koeffs;
            float prec = 0.0001f;

            float distXNat = falseNatChld.x() - native->basePoint.x();
            float distYNat = falseNatChld.y() - native->basePoint.y();
            float distZNat = falseNatChld.z() - native->basePoint.z();

            float distXCyb = chldPt->x() - cyber->basePoint.x();
            if(abs(distXCyb) < prec) koeffs.setX(1.0f);
            else koeffs.setX(distXNat / distXCyb);

            float distYCyb = chldPt->y() - cyber->basePoint.y();
            if(abs(distYCyb) < prec) koeffs.setY(1.0f);
            else koeffs.setY(distYNat / distYCyb);

            float distZCyb = chldPt->z() - cyber->basePoint.z();
            if(abs(distZCyb) < prec) koeffs.setZ(1.0f);
            else koeffs.setZ(distZNat / distZCyb);

            // --- apply koeffs ---
            *chldPt = (*chldPt - cyber->basePoint) * koeffs + cyber->basePoint;
            // ---
            *chldPt = rotatePoint3F(*chldPt, native->rotationCurrent.degToRad(), cyber->basePoint);

            // --- stl ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &pnt : tri.vertex){
                    pnt = rotatePoint3FBack(pnt, cyber->rotationCurrent.degToRad(), cyber->basePoint);
                    // --- apply koeffs ---
                    pnt = (pnt - cyber->basePoint) * koeffs + cyber->basePoint;
                    // --- rotate to native
                    pnt = rotatePoint3F(pnt, native->rotationCurrent.degToRad(), cyber->basePoint);
                }
        }
        else{} // return?

        cyber->rotationCurrent = native->rotationCurrent;
    }
}
