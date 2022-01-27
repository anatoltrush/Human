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
    skeleton->resetBones();
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
                // --- intersect basePt <-> childPt
                for(auto chPtI = thisChild->childrenPoints.begin(); chPtI != thisChild->childrenPoints.end(); chPtI++){
                    QVector3D ptBeg = thisChild->basePoint;
                    QVector3D ptInter;
                    QVector3D ptEnd = chPtI.value();
                    bool isInter = isIntersect(ptBeg, ptInter, ptEnd);
                    if(isInter){ // IF INTERSECT
                        // --- check parents have intersects ---
                        bool isParInter = false;
                        AbstractBone falseChild = *thisChild;
                        while (true) {
                            AbstractBone* thisParent = falseChild.parentPointer;
                            if(!thisParent){
                                isParInter = false;
                                break;
                            }
                            // ---
                            if(thisParent->intersections.find(falseChild.name) != thisParent->intersections.end()){
                                isParInter = true;
                                isWarning = true; // --- WARNING --- bad surface angle
                                break;
                            }
                            falseChild = *thisParent;
                        }
                        if(isParInter) continue;
                        // ---

                        thisChild->intersections.insert(chPtI.key(), ptInter);
                        if(!skeleton->isHuman) // --- one make real bone ---
                            thisChild->isExist = true;
                        cutAllLower(skeleton->bones[chPtI.key()], skeleton->isHuman);
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
    float precision = 0.0001f;
    std::vector<QVector3D> unique = makeUniquePts(pts, precision);

    // ---
    std::vector<man::Triangle> resVec;
    // ---
    if(unique.size() < 3){}
    else if(unique.size() == 3){
        Triangle addTri = Triangle(unique[0], unique[1], unique[2], QVector3D(0.0f, 0.0f, 1.0f), true);
        resVec.push_back(addTri);
    }
    else{
        QVector3D center = getCenter(unique);

        // --- calc all dist to center ---
        QMultiMap<float, QVector3D> pointsDist;
        for(size_t i = 0; i < unique.size(); i++){
            float distPt = center.distanceToPoint(unique[i]);
            pointsDist.insert(distPt, unique[i]);
        }

        // --- fill and reverse vector ---
        std::vector<QVector3D> sorted;
        for(auto iter = pointsDist.begin(); iter != pointsDist.end(); iter++)
            sorted.push_back(iter.value());
        std::reverse(sorted.begin(), sorted.end());
        Triangle startTri(sorted[0], sorted[1], sorted[2], QVector3D(0.0f, 0.0f, 1.0f), true);
        center = getCenter(startTri.toVector());
        std::vector<Triangle> tris;
        std::vector<QVector3D> outerContour;

        // --- check other points ---
        for(size_t i = 0; i < startTri.toVector().size(); i++){
            size_t nextInd = i + 1;
            if(nextInd == startTri.toVector().size())
                nextInd = 0;
            // ---
            QVector3D A = startTri.toVector()[i];
            QVector3D B = startTri.toVector()[nextInd];
            // ---
            QMap<float, QVector3D> mapAngles;
            std::vector<QVector3D> part;
            for(size_t j = 0; j < unique.size(); j++){
                QVector3D crossCoord;
                bool isCross = isLineCross(A, B, center, unique[j], crossCoord);
                if(isCross){
                    float ang = angle3Pts0_180(A, center, unique[j]);
                    mapAngles.insert(ang, unique[j]);
                }
            }
            if(mapAngles.size() > 0){
                std::vector<QVector3D> angsVec;
                for(auto angIt = mapAngles.begin(); angIt != mapAngles.end(); angIt++)
                    angsVec.push_back(angIt.value());
                // ---
                for(size_t k = 0; k < angsVec.size() - 1; k++){
                    Triangle tri(center, angsVec[k], angsVec[k + 1], QVector3D(0.0f, 0.0f, 1.0f), true);
                    tris.push_back(tri);
                    part.push_back(angsVec[k]);
                }
                Triangle lastTri(center, angsVec.back(), B, QVector3D(0.0f, 0.0f, 1.0f), true);
                tris.push_back(lastTri);
                part.push_back(angsVec.back());
            }
            outerContour.insert(outerContour.end(), part.begin(), part.end());
        }
        //smoothContour(tris, outerContour, center);
        // ---
        resVec.insert(resVec.end(), tris.begin(), tris.end());
    }
    return resVec;
}

float man::CutSurface::applyEqual(const QVector3D &pt)
{
    float res = planeEqual.x() * pt.x() + planeEqual.y() * pt.y() + planeEqual.z() * pt.z() + planeEqual.w();
    return res;
}

void man::CutSurface::smoothContour(std::vector<Triangle> &triangles, std::vector<QVector3D> &contour, const QVector3D &center)
{
    for(size_t i = 0; i < contour.size(); i++){
        size_t indOne = i + 1;
        if(indOne == contour.size()) indOne = 0;
        size_t indTwo = indOne + 1;
        if(indTwo == contour.size()) indTwo = 0;
        // ---
        QVector3D A = contour[i];
        QVector3D B = contour[indOne];
        QVector3D C = contour[indTwo];
        // ---
        Triangle tempTri(A, center, C, QVector3D(0, 0, 0), false);
        bool isPtIn = isInTriangle(tempTri.toVector(), B);
        if(isPtIn){
            float distAB = A.distanceToPoint(B);
            float distBC = B.distanceToPoint(C);
            float distAC = A.distanceToPoint(C);
            if(((distAB + distBC) - distAC) > 0.001f){
                Triangle newTri(A, B, C, QVector3D(0, 0, 1), true);
                triangles.push_back(newTri);
                contour.erase(contour.begin() + indOne);
                i--;
            }
        }
    }
}
