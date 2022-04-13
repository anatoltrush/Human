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
            // --- anchor ---
            cyber->anchorDirect = QVector3D((cyber->anchorDirect - cyber->basePoint) * koeff + cyber->basePoint);
        }
        else{} // return?
    }
}

void man::ReArranger::rotateBone(man::AbstractBone *native, man::AbstractBone *cyber)
{
    //if(cyber->name != "RightHand") return;
    if(cyber->name != "LeftHand") return;
    //if(cyber->name != "LeftForearm") return;
    for(auto natChildPnt = native->childrenPoints.begin(); natChildPnt != native->childrenPoints.end(); natChildPnt++){
        if(cyber->childrenPoints.find(natChildPnt.key()) != cyber->childrenPoints.end()){
            // --- --- --- XXX --- --- ---
            /*QVector3D newNativeY(natChildPnt.value().x(), chldPt->y(), natChildPnt.value().z());
            float angY = angle3Pts0_180(*chldPt, cyber->basePoint, newNativeY);
            Angle aY(0.0f, angY, 0.0f);
            *chldPt = rotatePoint3FBack(*chldPt, aY.degToRad(), cyber->basePoint);*/

            // --- --- --- 1) RESTORE --- --- ---
            // --- rotate child (C & N) ---
            /*C*/QVector3D* chldPt = &cyber->childrenPoints[natChildPnt.key()];
            *chldPt = rotatePoint3FBack(*chldPt, cyber->rotationCurrent.degToRad(), native->basePoint);

            /*N*/QVector3D* natPt = &native->childrenPoints[natChildPnt.key()];
            *natPt = rotatePoint3FBack(*natPt, native->rotationCurrent.degToRad(), native->basePoint);

            // --- rotate anchors (C & N) ---
            /*C*/cyber->anchorDirect = rotatePoint3FBack(cyber->anchorDirect, cyber->rotationCurrent.degToRad(), native->basePoint);
            /*N*/native->anchorDirect = rotatePoint3FBack(native->anchorDirect, native->rotationCurrent.degToRad(), native->basePoint);

            // --- --- --- 2) CALC ALIGN ANGLE --- --- ---
            // --- create points ---
            QVector3D anchorCyb(cyber->anchorDirect.x(), cyber->anchorDirect.y(), native->anchorDirect.z());
            QVector3D anchorNat(native->anchorDirect);
            QVector3D center(native->basePoint.x(), native->basePoint.y(), native->anchorDirect.z());
            float offset = 10.0f;
            QVector3D starX(center.x() - offset, center.y(), center.z());
            QVector3D starY(center.x(), center.y() - offset, center.z());

            // --- calc angle 0...360 ---
            float angleCyberX180 = calcAngle_0_180(starX, center, anchorCyb);
            float angleCyberY180 = calcAngle_0_180(starY, center, anchorCyb);
            float angleNatureX180 = calcAngle_0_180(starX, center, anchorNat);
            float angleNatureY180 = calcAngle_0_180(starY, center, anchorNat);

            float angleCyber360 = convert2angTo360Deg(angleCyberX180, angleCyberY180);
            float angleNature360 = convert2angTo360Deg(angleNatureX180, angleNatureY180);

            /*QVector3D anchorDown(cyber->basePoint.x(), cyber->basePoint.y(), cyber->anchorDirect.z());
            float dirDist = anchorDown.distanceToPoint(cyber->anchorDirect);
            QVector3D frontAnchor(anchorDown.x(), anchorDown.y() - dirDist, anchorDown.z());
            float angleZ = angle3Pts0_180(frontAnchor, anchorDown, cyber->anchorDirect);
            if((anchorDown.x() - frontAnchor.x()) < 0.0f)
                angleZ = 360.0f - angleZ;
            Angle angleAdditional(0.0f, 0.0f, angleZ);*/

            // --- rotate anchors align ---
            //cyber->anchorDirect = rotatePoint3FBack(cyber->anchorDirect, angleAdditional.degToRad(), cyber->basePoint);

            // --- rotate stl align ---
            /*for(auto& tri : cyber->stlObject.triangles)
                for(auto &pnt : tri.vertex){
                    pnt = rotatePoint3FBack(pnt, cyber->rotationCurrent.degToRad(), cyber->basePoint);
                    pnt = rotatePoint3FBack(pnt, angleAdditional.degToRad(), cyber->basePoint); // additional rotation
                }*/

            // --- --- --- 3) ROTATE TO NATIVE --- --- ---
            // --- rotate child ---
            //*C*/*chldPt = rotatePoint3F(*chldPt, native->rotationCurrent.degToRad(), native->basePoint);
            //*N*/*natPt = rotatePoint3F(*natPt, native->rotationCurrent.degToRad(), native->basePoint);

            // --- rotate anchors ---
            //*C*/cyber->anchorDirect = rotatePoint3F(cyber->anchorDirect, native->rotationCurrent.degToRad(), native->basePoint);
            //*N*/native->anchorDirect = rotatePoint3F(native->anchorDirect, native->rotationCurrent.degToRad(), native->basePoint);

            // --- stl ---
            for(auto& tri : cyber->stlObject.triangles)
                for(auto &pnt : tri.vertex)
                    pnt = rotatePoint3F(pnt, native->rotationCurrent.degToRad(), native->basePoint);

            // --- assign new angle ---
            cyber->rotationCurrent = native->rotationCurrent;
        }
    }
}

void man::ReArranger::stretchAndRotateBone(man::AbstractBone *native, man::AbstractBone *cyber)
{
    if(cyber->name != "LeftHand") return;
    for(auto natChildPnt = native->childrenPoints.begin(); natChildPnt != native->childrenPoints.end(); natChildPnt++){
        if(cyber->childrenPoints.find(natChildPnt.key()) != cyber->childrenPoints.end()){
            QVector3D* chldPt = &cyber->childrenPoints[natChildPnt.key()];
            *chldPt = rotatePoint3FBack(*chldPt, cyber->rotationCurrent.degToRad(), cyber->basePoint);
            QVector3D falseNatChld = natChildPnt.value();
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

float man::ReArranger::convert2angTo360Deg(float angleX, float angleY)
{
    angleX = 110.0f;
    angleY = 20.0f;

    float resAngle = 0.0f;
    float expectedY = 270.0f - angleX; // 270.0f is sector
    float difference = abs(expectedY - angleY);

    if(difference < 0.1f){ // good result
        return resAngle;// TODO:!!!
    }
    else{ // corrected result
        return resAngle;// TODO:!!!
    }
}
