#include "CutSurface.h"

man::CutSurface::CutSurface()
{
    color = colDeepPink;

    /*surface.vertex[0] = Point3F(3.0f, -2.0f, 4.0f); // NOTE: delete
    surface.vertex[1] = Point3F(-1.0f, 3.0f, 2.0f);
    surface.vertex[2] = Point3F(2.0f, 2.0f, 1.0f);*/

    surface.vertex[0] = Point3F(-120.0f, 100.0f, -60.0f); // NOTE: delete
    surface.vertex[1] = Point3F(120.0f, 100.0f, -60.0f);
    surface.vertex[2] = Point3F(0.0f, -120.0f, -60.0f);
}

void man::CutSurface::execute(AbstractSkeleton *skeleton)
{
    if(!skeleton) return;
    skeleton->resetBones();
    calcPlaneEquation();

    // find start bone
    AbstractBone* startBone = nullptr;
    QMap<QString, AbstractBone*>::iterator startIter;
    for (startIter = skeleton->bones.begin(); startIter != skeleton->bones.end(); startIter++)
        if(startIter.value()->parentOffset.str == notAvlbl)
            startBone = startIter.value();
    if(!startBone) return;

    // -----
    std::vector<AbstractBone*> vecParents = {startBone};
    while (true) {
        std::vector<AbstractBone*> vecChildren;
        for(size_t i = 0; i < vecParents.size(); i++)
            for(size_t j = 0; j < vecParents[i]->childrenPointers.size(); j++){
                AbstractBone* thisChild = vecParents[i]->childrenPointers[j];
                // ---
                thisChild->basePoint = &vecParents[i]->childrenPoints[thisChild->name];
                QMap<QString, Point3F>::iterator chIter;
                for (chIter = thisChild->childrenPoints.begin(); chIter != thisChild->childrenPoints.end(); chIter++){
                    Point3F ptBeg = *thisChild->basePoint;
                    Point3F ptInter;
                    Point3F ptEnd = chIter.value();
                    bool isInter = isIntersect(ptBeg, ptInter, ptEnd);
                    if(isInter){ // IF INTERSECT
                        thisChild->interSects.push_back(ptInter);
                        if(!skeleton->isHuman){
                            thisChild->isExist = true;
                            for(auto &tr : thisChild->stlObject.triangles)
                                tr.isGood = true;
                        }
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
    glLineWidth(2.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(color.r, color.g, color.b);
    glVertex3f(surface.vertex[0].x, surface.vertex[0].y, surface.vertex[0].z);
    glVertex3f(surface.vertex[1].x, surface.vertex[1].y, surface.vertex[1].z);
    glVertex3f(surface.vertex[2].x, surface.vertex[2].y, surface.vertex[2].z);
    glEnd();
    // --- center ---
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    calcCenter();
    glVertex3f(center.x, center.y, center.z);
    glEnd();
}

QMap<QString, QVariant> man::CutSurface::getPropertyList() const
{

}

bool man::CutSurface::isIntersect(const Point3F &ptBeg, Point3F &ptInter, Point3F &ptEnd)
{
    bool isInter = false;

    //N = VP ( B - A, C - A )
    Point3F N = vectorProduct(surface.vertex[1] - surface.vertex[0], surface.vertex[2] - surface.vertex[0]);

    //V = A - X
    Point3F V = surface.vertex[0] - ptBeg;

    // расстояние до плоскости по нормали
    //d = SP ( N, V )
    //W = Y - X
    float d = dotProduct(N, V);
    Point3F W = ptEnd - ptBeg;

    // приближение к плоскости по нормали при прохождении отрезка
    //e = SP ( N, W )
    float e =  dotProduct(N, W);

    //if( e!=0 )
    //  O = X + W * d/e;
    float prec = 0.001f;
    //if(e != 0.0f)
    if(e < -prec || e > prec){
        ptInter.x = ptBeg.x  +  W.x*d/e;
        ptInter.y = ptBeg.y  +  W.y*d/e;
        ptInter.z = ptBeg.z  +  W.z*d/e;

        //SP ( X - O, Y - O ) <=0
        float inter = dotProduct(ptInter - ptBeg, ptInter - ptEnd);
        if(inter < 0){ // if inter < 0 => отрезок пересекает, иначе нет
            isInter = true;
        }
        else isInter = false;
    }
    else isInter = false;

    return isInter;
}

void man::CutSurface::cutAllLower(AbstractBone *startBone, bool isHuman)
{
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

void man::CutSurface::cutSingleLower(AbstractBone *startBone, bool isHuman)
{
    for(auto &tr : startBone->stlObject.triangles){
        float pt0 = applyEqual(tr.vertex[0]);
        float pt1 = applyEqual(tr.vertex[1]);
        float pt2 = applyEqual(tr.vertex[2]);
        if((pt0 > 0.0f) && (pt1 > 0.0f) && (pt2 > 0.0f)){
            tr.isGood = !isHuman;
        }
        else{

        }
    }
}

man::Point3F man::CutSurface::vectorProduct(const Point3F &A, const Point3F &B)
{
    Point3F VP;
    VP.x = A.y * B.z - B.y * A.z;
    VP.y = A.z * B.x - B.z * A.x;
    VP.z = A.x * B.y - B.x * A.y;
    return VP;
}

float man::CutSurface::dotProduct(const Point3F &A, const Point3F &B)
{
    float vsp = A.x * B.x + A.y * B.y + A.z * B.z;
    return vsp;
}

void man::CutSurface::calcCenter() const
{
    center.x = (surface.vertex[0].x + surface.vertex[1].x + surface.vertex[2].x) / 3.0f;
    center.y = (surface.vertex[0].y + surface.vertex[1].y + surface.vertex[2].y) / 3.0f;
    center.z = (surface.vertex[0].z + surface.vertex[1].z + surface.vertex[2].z) / 3.0f;
}

void man::CutSurface::calcPlaneEquation()
{
    Point3F BA = surface.vertex[1] - surface.vertex[0];
    Point3F CA = surface.vertex[2] - surface.vertex[0];

    Point4F N = vectorProduct(BA, CA);
    N.d = -N.x * surface.vertex[0].x - N.y * surface.vertex[0].y - N.z * surface.vertex[0].z;

    equal = N;
}

float man::CutSurface::applyEqual(const Point3F &pt)
{
    float res = equal.x * pt.x + equal.y * pt.y + equal.z * pt.z + equal.d;
    return res;
}
