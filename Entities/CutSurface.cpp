#include "CutSurface.h"

man::CutSurface::CutSurface()
{
    color = Qt::magenta;

    /*surface.vertex[0] = QVector3D(-20.0f, -40.0f, 15.0f); // NOTE: delete VERT
    surface.vertex[1] = QVector3D(-20.0f, 40.0f, 15.0f);
    surface.vertex[2] = QVector3D(-20.0f, 0.0f, -60.0f);*/

    /*surface.vertex[0] = QVector3D(3.0f, -2.0f, 4.0f); // NOTE: delete ANGLE
    surface.vertex[1] = QVector3D(-1.0f, 3.0f, 2.0f);
    surface.vertex[2] = QVector3D(2.0f, 2.0f, 1.0f);*/

    surface.vertex[0] = QVector3D(-120.0f, 100.0f, -80.0f); // NOTE: delete HORIZ
    surface.vertex[1] = QVector3D(120.0f, 100.0f, -80.0f);
    surface.vertex[2] = QVector3D(0.0f, -120.0f, -60.0f);

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
    equal = calcPlaneEquation(surface.vertex[0], surface.vertex[1], surface.vertex[2]);
    equal.normalize();

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
                thisChild->basePoint = &vecParents[i]->childrenPoints[thisChild->name];
                QMap<QString, QVector3D>::iterator chIter;
                for (chIter = thisChild->childrenPoints.begin(); chIter != thisChild->childrenPoints.end(); chIter++){
                    QVector3D ptBeg = *thisChild->basePoint;
                    QVector3D ptInter;
                    QVector3D ptEnd = chIter.value();
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
                            QMap<QString, QVector3D>::iterator findInter = thisParent->intersections.find(falseChild.name);
                            if(findInter != thisParent->intersections.end()){
                                isParInter = true;
                                isWarning = true; // --- WARNING --- bad surface angle
                                break;
                            }
                            falseChild = *thisParent;
                        }
                        if(isParInter) continue;
                        // ---

                        thisChild->intersections.insert(chIter.key(), ptInter);
                        if(!skeleton->isHuman) // --- one make real bone ---
                            thisChild->isExist = true;
                        cutAllLower(skeleton->bones[chIter.key()], skeleton->isHuman);
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

void man::CutSurface::drawObjectGL() const
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(2.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(color.red(), color.green(), color.blue());
    glVertex3f(surface.vertex[0].x(), surface.vertex[0].y(), surface.vertex[0].z());
    glVertex3f(surface.vertex[1].x(), surface.vertex[1].y(), surface.vertex[1].z());
    glVertex3f(surface.vertex[2].x(), surface.vertex[2].y(), surface.vertex[2].z());
    glEnd();
    // --- center ---
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    calcCenter();
    glVertex3f(center.x(), center.y(), center.z());
    glEnd();
}

QMap<QString, QVariant> man::CutSurface::getPropertyList() const
{

}

bool man::CutSurface::isIntersect(const QVector3D &ptBeg, QVector3D &ptInter, QVector3D &ptEnd)
{
    bool isInter = false;

    //N = VP ( B - A, C - A )
    QVector3D N = vectorProduct(surface.vertex[1] - surface.vertex[0], surface.vertex[2] - surface.vertex[0]);
    N.normalize();

    //V = A - X
    QVector3D V = surface.vertex[0] - ptBeg;

    // расстояние до плоскости по нормали
    //d = SP ( N, V )
    //W = Y - X
    float d = dotProduct(N, V);
    QVector3D W = ptEnd - ptBeg;

    // приближение к плоскости по нормали при прохождении отрезка
    //e = SP ( N, W )
    float e =  dotProduct(N, W);

    //if( e!=0 )
    //  O = X + W * d/e;
    float prec = 0.001f;
    //if(e != 0.0f)
    if(e < -prec || e > prec){
        ptInter.setX(ptBeg.x()  +  W.x() * d / e);
        ptInter.setY(ptBeg.y()  +  W.y() * d / e);
        ptInter.setZ(ptBeg.z()  +  W.z() * d / e);

        //SP ( X - O, Y - O ) <=0
        float inter = dotProduct(ptInter - ptBeg, ptInter - ptEnd);
        if(inter < 0.0f) // if inter < 0 => отрезок пересекает, иначе нет
            isInter = isInContour(surface.toVector(), ptInter);
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
                QMultiMap<float, int>::iterator it;
                for (it = pts.begin(); it != pts.end(); it++)
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
                QMultiMap<float, int>::iterator it;
                for (it = pts.begin(); it != pts.end(); it++)
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
                QMultiMap<float, int>::iterator it;
                for (it = pts.begin(); it != pts.end(); it++)
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
                QMultiMap<float, int>::iterator it;
                for (it = pts.begin(); it != pts.end(); it++)
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
}

std::vector<man::Triangle> man::CutSurface::makePlug(std::vector<QVector3D> &pts)
{
    float precision = 0.001f;
    std::vector<QVector3D> unique = makeUnique(pts, precision);

    // ---
    std::vector<man::Triangle> resVec;
    // ---
    /*if(unique.size() < 3){}
    else if(unique.size() == 3){
        Triangle addTri = Triangle(unique[0], unique[1], unique[2], QVector3D(0.0f, 0.0f, 1.0f), true);
        resVec.push_back(addTri);
    }
    else{
        QVector3D center;
        for(size_t i = 0; i < unique.size(); i++)
            center += unique[i];
        center /= unique.size();
        // --- farest ---
        float maxDist = 0.0f;
        QVector3D farest;
        for(size_t i = 0; i < unique.size(); i++){
            float dist = center.distanceToPoint(unique[i]);
            if(dist > maxDist){
                farest = unique[i];
                maxDist = dist;
            }
        }
        // --- right line ---
        QVector3D perpend(farest.x(), farest.y(), 0.0f);
        QVector2D right2d(perpend.toVector2D());
        float zPos = 0.0f;
        QVector3D right3d(right2d, zPos);
        // ---
        QMap<float, QVector3D*> outs;
        for(size_t i = 0; i < unique.size(); i++){
            float ang = angle3Points(farest, center, unique[i], QVector3D(equal.x(), equal.y(), equal.z()));
            outs.insert(ang, &unique[i]);
        }
        std::vector<QVector3D*> vers;
        QMap<float, QVector3D*>::iterator outIter;
        for (outIter = outs.begin(); outIter != outs.end(); outIter++)
            vers.push_back(outIter.value());

        // --- make triangles ---
        for(size_t i = 0; i < vers.size(); i++){
            size_t nextInd = i + 1;
            if(nextInd == vers.size())
                nextInd = 0;
            Triangle addTri(center, *vers[i], *vers[nextInd], QVector3D(0.0f, 0.0f, 1.0f), true);
            resVec.push_back(addTri);
        }

        int a = 5;

        // --- make triangles ---
        /*for(size_t i = 0; i < hours.size(); i++){
            size_t nextInd = i + 1;
            if(nextInd == hours.size())
                nextInd = 0;

            Triangle addTri(hours[i], center, hours[nextInd], QVector3D(0.0f, 0.0f, 1.0f), true);
            resVec.push_back(addTri);
        }*/
    //}
    return resVec;
}

float man::CutSurface::dotProduct(const QVector3D &A, const QVector3D &B)
{
    float vsp = A.x() * B.x() + A.y() * B.y() + A.z() * B.z();
    return vsp;
}

void man::CutSurface::calcCenter() const
{
    center.setX((surface.vertex[0].x() + surface.vertex[1].x() + surface.vertex[2].x()) / 3);
    center.setY((surface.vertex[0].y() + surface.vertex[1].y() + surface.vertex[2].y()) / 3);
    center.setZ((surface.vertex[0].z() + surface.vertex[1].z() + surface.vertex[2].z()) / 3);
}

float man::CutSurface::applyEqual(const QVector3D &pt)
{
    float res = equal.x() * pt.x() + equal.y() * pt.y() + equal.z() * pt.z() + equal.w();
    return res;
}
