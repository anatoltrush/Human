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
                // --- make smthng ---
                if(cyber.skeleton->bones.find(nativeChild->name) != cyber.skeleton->bones.end()){
                    AbstractBone* cyberChild = cyber.skeleton->bones[nativeChild->name];
                    if(cyberChild){
                        offsetBone(nativeChild, cyberChild);
                        scaleBone(nativeChild, cyberChild);
                        rotateBone(nativeChild, cyberChild);
                    }
                }
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
    cyber->anchorDirect -= diffDist;
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
    float summScale = 0.0f;
    float averScale = 0.0f;
    int averCount = 0;
    // ---
    for(auto it = native->childrenPoints.begin(); it != native->childrenPoints.end(); it++){
        if(cyber->childrenPoints.find(it.key()) != cyber->childrenPoints.end()){
            float distNative = native->basePoint.distanceToPoint(it.value());
            float distCyber = cyber->basePoint.distanceToPoint(cyber->childrenPoints[it.key()]);
            float koeff = distNative / distCyber;
            // --- average scale ---
            summScale += koeff;
            averCount++;
            averScale = summScale / averCount;
            // --- chl pts ---
            QVector3D* chldPt = &cyber->childrenPoints[it.key()];
            *chldPt = (*chldPt - cyber->basePoint) * koeff + cyber->basePoint;
        }
    }
    // --- stl --- // TODO: need more difficult
    for(auto& tri : cyber->stlObject.triangles)
        for(auto &vr : tri.vertex)
            vr = QVector3D((vr - cyber->basePoint) * averScale + cyber->basePoint);
    // --- anchor ---
    cyber->anchorDirect = QVector3D((cyber->anchorDirect - cyber->basePoint) * averScale + cyber->basePoint);
}

void man::ReArranger::rotateBone(man::AbstractBone *native, man::AbstractBone *cyber)
{
    //if(cyber->name != "LeftHand") return;
    for(auto natChildPnt = native->childrenPoints.begin(); natChildPnt != native->childrenPoints.end(); natChildPnt++){
        if(cyber->childrenPoints.find(natChildPnt.key()) != cyber->childrenPoints.end()){
            // --- --- --- 1) RESTORE --- --- ---
            // --- rotate child (C & N) ---
            /*C*/QVector3D* chldPt = &cyber->childrenPoints[natChildPnt.key()];
            *chldPt = rotatePoint3FBack(*chldPt, cyber->rotationCurrent.degToRad(), native->basePoint);
            /*N*/QVector3D* natPt = &native->childrenPoints[natChildPnt.key()];
            *natPt = rotatePoint3FBack(*natPt, native->rotationCurrent.degToRad(), native->basePoint);

            // --- rotate anchors (C & N) ---
            /*C*/cyber->anchorDirect = rotatePoint3FBack(cyber->anchorDirect, cyber->rotationCurrent.degToRad(), native->basePoint);
            /*N*/native->anchorDirect = rotatePoint3FBack(native->anchorDirect, native->rotationCurrent.degToRad(), native->basePoint);

            // --- rotate stl ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &pnt : tri.vertex)
                    pnt = rotatePoint3FBack(pnt, cyber->rotationCurrent.degToRad(), cyber->basePoint);

            // --- --- --- 2) CALC ALIGN ANGLE --- --- ---
            // --- create points ---
            QVector3D anchorCyb(cyber->anchorDirect.x(), cyber->anchorDirect.y(), native->anchorDirect.z());
            QVector3D anchorNat(native->anchorDirect);
            QVector3D center(native->basePoint.x(), native->basePoint.y(), native->anchorDirect.z());
            float offset = 10.0f;
            QVector3D starX(center.x() - offset, center.y(), center.z());
            QVector3D starY(center.x(), center.y() - offset, center.z());

            // --- calc angle 0...360 ---
            float angleYCyber360 = calcAngleY360(starX, center, starY, anchorCyb);
            float angleYNature360 = calcAngleY360(starX, center, starY, anchorNat);
            Angle angleDifferZ(0.0f, 0.0f, angleYNature360 - angleYCyber360);

            // --- rotate anchors align ---
            cyber->anchorDirect = rotatePoint3F(cyber->anchorDirect, angleDifferZ.degToRad(), cyber->basePoint);

            // --- rotate stl align ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &pnt : tri.vertex)
                    pnt = rotatePoint3F(pnt, angleDifferZ.degToRad(), cyber->basePoint); // additional rotation

            // --- --- --- 3) ROTATE TO NATIVE --- --- ---
            // --- rotate child ---
            /*C*/*chldPt = rotatePoint3F(*chldPt, native->rotationCurrent.degToRad(), native->basePoint);
            /*N*/*natPt = rotatePoint3F(*natPt, native->rotationCurrent.degToRad(), native->basePoint);

            // --- rotate anchors ---
            /*C*/cyber->anchorDirect = rotatePoint3F(cyber->anchorDirect, native->rotationCurrent.degToRad(), native->basePoint);
            /*N*/native->anchorDirect = rotatePoint3F(native->anchorDirect, native->rotationCurrent.degToRad(), native->basePoint);

            // --- stl ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &pnt : tri.vertex)
                    pnt = rotatePoint3F(pnt, native->rotationCurrent.degToRad(), native->basePoint);

            // --- assign new angle ---
            cyber->rotationCurrent = native->rotationCurrent;
        }
    }
}

float man::ReArranger::calcAngleY360(const QVector3D &starX, const QVector3D &center, const QVector3D &starY, const QVector3D &pt)
{
    float angleX180 = calcAngle_0_180(starX, center, pt);
    float angleY180 = calcAngle_0_180(starY, center, pt);

    if(angleY180 > 90.0f){
        float expectedX = 270.0f - angleY180; // 270.0f is sector
        float difference = abs(expectedX - angleX180);
        if(difference < 0.1f) return angleY180;
        else return 360.0f - angleY180;
    }
    else{
        float expectedX = 90.0f + angleY180; // 90.0f is sector
        float difference = abs(expectedX - angleX180);
        if(difference < 0.1f) return angleY180;
        else return 360.0f - angleY180;
    }
}
