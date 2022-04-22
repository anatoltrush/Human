#include "CutSurface.h"

man::CutSurface::CutSurface()
{
    color = Qt::magenta;

    /*planeSurface.vertex[0] = QVector3D(-20.0f, -40.0f, 15.0f); // NOTE: delete VERT
    planeSurface.vertex[1] = QVector3D(-20.0f, 40.0f, 15.0f);
    planeSurface.vertex[2] = QVector3D(-20.0f, 0.0f, -60.0f);*/

    /*surface.vertex[0] = QVector3D(3.0f, -2.0f, 4.0f); // NOTE: delete ANGLE
    surface.vertex[1] = QVector3D(-1.0f, 3.0f, 2.0f);
    surface.vertex[2] = QVector3D(2.0f, 2.0f, 1.0f);*/

    planeSurface.vertex[0] = QVector3D(-120.0f, 100.0f, -80.0f); // NOTE: delete HORIZ
    planeSurface.vertex[1] = QVector3D(120.0f, 100.0f, -80.0f);
    planeSurface.vertex[2] = QVector3D(0.0f, -120.0f, -50.0f);

    /*surface.vertex[0] = QVector3D(0.0f, 100.0f, -60.0f); // NOTE: delete HORIZ HALF
    surface.vertex[1] = QVector3D(120.0f, 100.0f, -60.0f);
    surface.vertex[2] = QVector3D(0.0f, -120.0f, -60.0f);*/

    /*surface.vertex[0] = QVector3D(-1.0f, 1.0f, -60.0f); // NOTE: delete HORIZ small
    surface.vertex[1] = QVector3D(1.0f, 1.0f, -60.0f);
    surface.vertex[2] = QVector3D(0.0f, -1.0f, -60.0f);*/
}

void man::CutSurface::execute(AbstractSkeleton *skeleton, bool &isWarning)
{
    if(!skeleton) return;
    skeleton->resetBonesExist();
    planeEqual = calcPlaneEquation(planeSurface.vertex[0], planeSurface.vertex[1], planeSurface.vertex[2]);
    planeEqual.normalize();

    // find start bone
    AbstractBone* startBone = skeleton->getStartBone();
    if(!startBone) return;

    // -----
    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                if(!thisChild) continue;
                // --- intersect basePt <-> childPt
                for(auto childrenPointI = thisChild->childrenPoints.begin(); childrenPointI != thisChild->childrenPoints.end(); childrenPointI++){
                    QVector3D ptBeg = thisChild->basePoint;
                    QVector3D ptInter;
                    QVector3D ptEnd = childrenPointI.value();
                    bool isIntersected = isIntersect(ptBeg, ptInter, ptEnd);
                    if(isIntersected){
                        // --- check parents have intersects ---
                        bool isParentIntersected = false;
                        AbstractBone childCopy = *thisChild;
                        while (true) {
                            AbstractBone* thisParent = childCopy.parentPointer;
                            if(!thisParent){
                                isParentIntersected = false;
                                break;
                            }
                            // ---
                            if(thisParent->intersections.find(childCopy.name) != thisParent->intersections.end()){
                                isParentIntersected = true;
                                isWarning = true; // --- WARNING --- bad surface angle
                                break;
                            }
                            childCopy = *thisParent;
                        }
                        if(isParentIntersected) continue; // not cut off

                        // --- cut off ---
                        thisChild->intersections.insert(childrenPointI.key(), ptInter);
                        thisChild->isExist = !skeleton->isHuman;
                        if(childrenPointI.key() != notAvlbl)
                            cutAllLower(skeleton->bones[childrenPointI.key()], skeleton->isHuman);
                        cutSingleLower(thisChild, skeleton->isHuman);
                    }
                }
                // ---
                vecChildren.push_back(thisChild);
            }
        // -----
        if(vecChildren.empty()) break;
        vecParents = vecChildren;
    }
}

void man::CutSurface::drawObjectGL()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(2.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(color.red(), color.green(), color.blue());
    glVertex3f(planeSurface.vertex[0].x(), planeSurface.vertex[0].y(), planeSurface.vertex[0].z());
    glVertex3f(planeSurface.vertex[1].x(), planeSurface.vertex[1].y(), planeSurface.vertex[1].z());
    glVertex3f(planeSurface.vertex[2].x(), planeSurface.vertex[2].y(), planeSurface.vertex[2].z());
    glEnd();
    // --- center ---
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    planeCenter = getCenter(planeSurface.toVector());
    glVertex3f(planeCenter.x(), planeCenter.y(), planeCenter.z());
    glEnd();
}

QMap<QString, QVariant> man::CutSurface::getPropertyList() const
{
    QMap<QString, QVariant> props;
    props["CutSurface"] = "<-CutSurface->";
    return props;
}

bool man::CutSurface::isIntersect(const QVector3D &ptBeg, QVector3D &ptInter, QVector3D &ptEnd)
{
    bool isInter = false;

    //N = VP ( B - A, C - A )
    QVector3D N = vectorProduct(planeSurface.vertex[1] - planeSurface.vertex[0], planeSurface.vertex[2] - planeSurface.vertex[0]);
    N.normalize();

    //V = A - X
    QVector3D V = planeSurface.vertex[0] - ptBeg;

    // расстояние до плоскости по нормали
    //d = SP ( N, V )
    //W = Y - X
    float d = QVector3D::dotProduct(N, V);
    QVector3D W = ptEnd - ptBeg;

    // приближение к плоскости по нормали при прохождении отрезка
    //e = SP ( N, W )
    float e =  QVector3D::dotProduct(N, W);

    //if( e!=0 )
    //  O = X + W * d/e;
    float prec = 0.001f;
    //if(e != 0.0f)
    if(e < -prec || e > prec){
        ptInter.setX(ptBeg.x()  +  W.x() * d / e);
        ptInter.setY(ptBeg.y()  +  W.y() * d / e);
        ptInter.setZ(ptBeg.z()  +  W.z() * d / e);

        //SP ( X - O, Y - O ) <=0
        float inter = QVector3D::dotProduct(ptInter - ptBeg, ptInter - ptEnd);
        if(inter < 0.0f) // if inter < 0 => отрезок пересекает, иначе нет
            isInter = isInTriangle(planeSurface.toVector(), ptInter);
        else isInter = false;
    }
    else isInter = false;

    return isInter;
}

void man::CutSurface::cutAllLower(AbstractBone *startBone, bool isHuman)
{
    if(!startBone) return;
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
    for(const auto &bn : allChildBones){
        bn->isExist = !isHuman;
        for(auto &tr : bn->stlObject.triangles)
            tr.isGood = !isHuman;
        calcAddProperties(bn->stlObject, false);
    }
}

void man::CutSurface::cutSingleLower(AbstractBone *bone, bool isHuman)
{
    std::vector<QVector3D> plugPts;
    // -----
    for(auto &tr : bone->stlObject.triangles){
        int res = 0;
        QMultiMap<float, int>pts;
        for(int i = 0; i < 3; i++){
            float pos = applyEqual(tr.vertex[i]);            
            pts.insert(pos, i);
            if(pos > 0.0f) res++;
        }

        // -----
        if(isHuman){
            if(res == 3){ // all triangle down
                tr.isGood = !isHuman;
            }
            else if(res == 2){ // split 2 pt down
                tr.isGood = !isHuman;
                // ---
                std::vector<QVector3D> vrxReal;
                for (auto it = pts.begin(); it != pts.end(); it++)
                    vrxReal.push_back(tr.vertex[it.value()]);

                QVector3D X, Z;
                bool is01 = isIntersect(vrxReal[0], X, vrxReal[1]);
                bool is02 = isIntersect(vrxReal[0], Z, vrxReal[2]);
                if(!is01 || !is02) continue;

                Triangle sector0(X, vrxReal[0], Z, tr.normal, isHuman);
                bone->stlObject.additional.push_back(sector0);
                // ---
                plugPts.push_back(X);
                plugPts.push_back(Z);
            }
            else if(res == 1){ // split 1 pt down
                tr.isGood = !isHuman;
                // ---
                std::vector<QVector3D> vrxReal;
                for (auto it = pts.begin(); it != pts.end(); it++)
                    vrxReal.push_back(tr.vertex[it.value()]);

                QVector3D X, Y, Z;
                Y.setX((vrxReal[0].x() + vrxReal[1].x()) / 2);
                Y.setY((vrxReal[0].y() + vrxReal[1].y()) / 2);
                Y.setZ((vrxReal[0].z() + vrxReal[1].z()) / 2);

                bool is20 = isIntersect(vrxReal[2], X, vrxReal[0]);
                bool is21 = isIntersect(vrxReal[2], Z, vrxReal[1]);
                if(!is20 || !is21) continue;

                Triangle sector0(vrxReal[0], Y, X, tr.normal, isHuman);
                Triangle sector1(X, Y, Z, tr.normal, isHuman);
                Triangle sector2(Y, vrxReal[1], Z, tr.normal, isHuman);

                bone->stlObject.additional.push_back(sector0);
                bone->stlObject.additional.push_back(sector1);
                bone->stlObject.additional.push_back(sector2);
                // ---
                plugPts.push_back(X);
                plugPts.push_back(Z);
            }
            else{ /* res == 0, all triangle up, do nothing*/ }
        }
        else{
            if(res == 3){
                tr.isGood = !isHuman;
            } // all triangle down
            else if(res == 2){ // split 2 pt down
                std::vector<QVector3D> vrxReal;
                for(auto it = pts.begin(); it != pts.end(); it++)
                    vrxReal.push_back(tr.vertex[it.value()]);

                QVector3D X, Y, Z;
                Y.setX((vrxReal[1].x() + vrxReal[2].x()) / 2);
                Y.setY((vrxReal[1].y() + vrxReal[2].y()) / 2);
                Y.setZ((vrxReal[1].z() + vrxReal[2].z()) / 2);

                bool is01 = isIntersect(vrxReal[0], X, vrxReal[1]);
                bool is02 = isIntersect(vrxReal[0], Z, vrxReal[2]);
                if(!is01 || !is02) continue;

                Triangle sector0(vrxReal[1], X, Y, tr.normal, !isHuman);
                Triangle sector1(Z, Y, X, tr.normal, !isHuman);
                Triangle sector2(Y, Z, vrxReal[2], tr.normal, !isHuman);

                bone->stlObject.additional.push_back(sector0);
                bone->stlObject.additional.push_back(sector1);
                bone->stlObject.additional.push_back(sector2);
                // ---
                plugPts.push_back(X);
                plugPts.push_back(Z);
            }
            else if(res == 1){ // split 1 pt down
                std::vector<QVector3D> vrxReal;
                for (auto it = pts.begin(); it != pts.end(); it++)
                    vrxReal.push_back(tr.vertex[it.value()]);

                QVector3D X, Z;
                bool is20 = isIntersect(vrxReal[2], X, vrxReal[0]);
                bool is21 = isIntersect(vrxReal[2], Z, vrxReal[1]);
                if(!is20 || !is21) continue;

                Triangle sector0(X, Z, vrxReal[2], tr.normal, !isHuman);
                bone->stlObject.additional.push_back(sector0);
                // ---
                plugPts.push_back(X);
                plugPts.push_back(Z);
            }
            else{ /* res == 0, all triangle up, do nothing*/ }
        }
    }
    std::vector<Triangle> plug = makePlug(plugPts);
    bone->stlObject.additional.insert(bone->stlObject.additional.end(), plug.begin(), plug.end());
    calcAddProperties(bone->stlObject, false);
}

std::vector<man::Triangle> man::CutSurface::makePlug(std::vector<QVector3D> &pts)
{
    std::vector<Triangle> triangles;

    // 0) ---
    float precision = 0.0001f;
    std::vector<QVector3D> cloud = makeUniquePts(pts, precision);
    // ---
    if(cloud.size() < 3){
        qWarning() << "WARNING! Only 2 points got (CutSurface::makePlug)";
        return triangles;
    }
    if(cloud.size() == 3){
        Triangle addTri = Triangle(cloud[0], cloud[1], cloud[2], QVector3D(0.0f, 0.0f, 1.0f), true);
        triangles.push_back(addTri);
        return triangles;
    }

    // 1) --- find 1st pt ---
    QVector3D firstPt(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    QVector3D starDown;

    float aveX = 0.0f;
    for(const auto &pt : cloud)
        aveX += pt.x();
    aveX /= cloud.size();

    float aveY = 0.0f;
    for(const auto &pt : cloud)
        aveY += pt.y();
    aveY /= cloud.size();

    float aveZ = 0.0f;
    for(const auto &pt : cloud)
        aveZ += pt.z();
    aveZ /= cloud.size();

    if(aveX > aveY && aveX > aveZ){ // X
        for(size_t i = 0; i < cloud.size(); i++)
            if(cloud[i].x() < firstPt.x()){
                firstPt = cloud[i];
                starDown = QVector3D(firstPt.x() - 1.0f, firstPt.y(), firstPt.z());
            }
    }
    if(aveY > aveX && aveY > aveZ){ // Y
        for(size_t i = 0; i < cloud.size(); i++)
            if(cloud[i].y() < firstPt.y()){
                firstPt = cloud[i];
                starDown = QVector3D(firstPt.x(), firstPt.y() - 1.0f, firstPt.z());
            }
    }
    if(aveZ > aveX && aveZ > aveY){ // Z
        for(size_t i = 0; i < cloud.size(); i++)
            if(cloud[i].z() < firstPt.z()){
                firstPt = cloud[i];
                starDown = QVector3D(firstPt.x(), firstPt.y(), firstPt.z() - 1.0f);
            }
    }

    // 2) --- find 2nd pt ---
    QVector3D secondPt;
    float minAngSec = 180.0f;
    for(size_t ind = 0; ind < cloud.size(); ind++){
        if(cloud[ind] == firstPt) continue;
        float currAng = calcAngle_0_180(starDown, firstPt, cloud[ind]);
        if(currAng < minAngSec){
            secondPt = cloud[ind];
            minAngSec = currAng;
        }
    }

    // 3) ---
    std::vector<QVector3D> outer {firstPt, secondPt};
    while (true) {
        QVector3D last = outer[outer.size() - 1];
        QVector3D prev = outer[outer.size() - 2];

        float maxAng = 0.0f;
        QVector3D nextPt;
        for(size_t i = 0; i < cloud.size(); i++){
            //if(std::find(outer.begin(), outer.end(), cloud[i]) != outer.end()) continue;
            if(cloud[i] == prev || cloud[i] == last) continue;
            float currAng = calcAngle_0_180(prev, last, cloud[i]);
            if(currAng > maxAng){
                nextPt = cloud[i];
                maxAng = currAng;
            }
        }
        if(nextPt == firstPt) break;
        outer.push_back(nextPt);
    }

    // 4) --- make triangles ---
    QVector3D center = getCenter(outer);
    for(size_t j = 0; j < outer.size(); j++){
        size_t jNext = j + 1;
        if(jNext == outer.size()) jNext = 0;
        Triangle tri(outer[j], center, outer[jNext], QVector3D(0.0f, 0.0f, 1.0f), true);
        triangles.push_back(tri);
    }
    return triangles;
}

float man::CutSurface::applyEqual(const QVector3D &pt)
{
    float res = planeEqual.x() * pt.x() + planeEqual.y() * pt.y() + planeEqual.z() * pt.z() + planeEqual.w();
    return res;
}
