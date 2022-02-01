#include "ExtraMath.h"

QVector3D man::rotatePoint3FBack(const QVector3D &point, const QVector3D &angleRad, const QVector3D &basePoint)
{
    QVector3D resPt = point;
    //resPt = rotatePoint3F(resPt, -angleRad, basePoint); // BUG: !wrong way
    resPt = rotatePoint3F(resPt, Angle(0.0f, 0.0f, -angleRad.z()), basePoint);
    resPt = rotatePoint3F(resPt, Angle(0.0f, -angleRad.y(), 0.0f), basePoint);
    resPt = rotatePoint3F(resPt, Angle(-angleRad.x(), 0.0f, 0.0f), basePoint);
    return resPt;
}

QVector3D man::rotatePoint3F(const QVector3D &point, const QVector3D &angleRad, const QVector3D &basePoint)
{
    QVector3D diffPt = point - basePoint;
    QVector3D aftXrot = rotatePoint3FX(diffPt, angleRad.x());
    QVector3D aftYrot = rotatePoint3FY(aftXrot, angleRad.y());
    QVector3D aftZrot = rotatePoint3FZ(aftYrot, angleRad.z());

    aftZrot += basePoint;
    return aftZrot;
}

QVector3D man::rotatePoint3FX(QVector3D point, const float &angX)
{
    QVector3D resPoint;
    resPoint.setX(point.x());
    resPoint.setY(point.y() * cos(angX) - point.z() * sin(angX));
    resPoint.setZ(point.y() * sin(angX) + point.z() * cos(angX));
    return resPoint;
}

QVector3D man::rotatePoint3FY(QVector3D point, const float &angY)
{
    QVector3D resPoint;
    resPoint.setX(point.x() * cos(angY) + point.z() * sin(angY));
    resPoint.setY(point.y());
    resPoint.setZ(-point.x() * sin(angY) + point.z() * cos(angY));
    return resPoint;
}

QVector3D man::rotatePoint3FZ(QVector3D point, const float &angZ)
{
    QVector3D resPoint;
    resPoint.setX(point.x() * cos(angZ) - point.y() * sin(angZ));
    resPoint.setY(point.x() * sin(angZ) + point.y() * cos(angZ));
    resPoint.setZ(point.z());
    return resPoint;
}

float man::squareTriangle(const QVector3D &A, const QVector3D &B, const QVector3D &C)
{
    float ab = A.distanceToPoint(B);
    float bc = B.distanceToPoint(C);
    float ca = C.distanceToPoint(A);

    float per = (ab + bc + ca) / 2.0f;
    float sqrTriangle = sqrt(per * (per - ab) * (per - bc) * (per - ca));

    return sqrTriangle;
}

float man::squarePolygon(std::vector<QVector3D> &contour)
{
    // TODO: implement | float man::squarePolygon(std::vector<man::Point3F> &contour)
    float square = 0.0f;
    return square;
}

bool man::isInTriangle(const std::vector<QVector3D> &contour, const QVector3D &pt)
{
    // float contSquare = squarePolygon(contour); // FIXME: change to squarePolygon()
    float contourSquare = squareTriangle(contour[0], contour[1], contour[2]);

    //float partsSummSqr = 0.0f; // error!
    uint64_t partsSummSqr = 0;
    for(size_t i = 0; i < contour.size(); i++){
        size_t nextInd = i + 1;
        if(nextInd == contour.size())
            nextInd = 0;

        QVector3D A = contour[i];
        QVector3D B = pt;
        QVector3D C = contour[nextInd];

        float triSqare = squareTriangle(A, B, C);
        partsSummSqr += triSqare;
    }
    if(partsSummSqr > contourSquare)
        return false;
    else
        return true;
}

std::vector<QVector3D> man::makeUniquePts(const std::vector<QVector3D> &pts, float precision)
{
    std::vector<QVector3D> unique = pts;
    for(size_t i = 0; i < unique.size(); i++){
        for(size_t j = 0; j < unique.size(); j++){
            if(i == j) continue;
            float dist = unique[i].distanceToPoint(unique[j]);
            if(dist < precision){
                unique.erase(unique.begin() + i);
                i--;
            }
        }
    }
    return unique;
}

std::vector<QVector3D> man::getPtsFromTris(const std::vector<man::Triangle> &tris, float precision)
{
    std::vector<QVector3D>resVec;
    for(const auto &tr : tris){
        resVec.push_back(tr.vertex[0]);
        resVec.push_back(tr.vertex[1]);
        resVec.push_back(tr.vertex[2]);
    }
    // ---
    resVec = makeUniquePts(resVec, precision);
    return resVec;
}

QVector3D man::vectorProduct(const QVector3D &A, const QVector3D &B)
{
    QVector3D VP;
    VP.setX(A.y() * B.z() - B.y() * A.z());
    VP.setY(A.z() * B.x() - B.z() * A.x());
    VP.setZ(A.x() * B.y() - B.x() * A.y());
    return VP;
}

QVector4D man::calcPlaneEquation(const QVector3D &pt0, QVector3D &pt1, const QVector3D &pt2)
{
    QVector3D BA = pt1 - pt0;
    QVector3D CA = pt2 - pt0;

    QVector3D N3 = vectorProduct(BA, CA);
    QVector4D N(N3);
    N.setW(-N.x() * pt0.x() - N.y() * pt0.y() - N.z() * pt0.z());

    return N;
}

float man::angle3Pts0_180(const QVector3D &pt0, QVector3D &mid, const QVector3D &pt1)
{
    QVector3D v1 = pt0 - mid;
    QVector3D v2 = pt1 - mid;

    QVector3D cross = QVector3D::crossProduct(v1, v2);
    float dot = QVector3D::dotProduct(v1, v2);

    float angle = std::atan2(cross.length(), dot);
    float degree = angle * 180.0 / M_PI;

    return degree;
}

man::Angle man::angle3Pts0_180Reverse(const QVector3D &pt, QVector3D &mid)
{
    // find Z
    QVector3D starX(mid.x(), mid.y() - 1, mid.z());
    QVector3D ptZ(pt.x(), pt.y(), mid.z());
    float angZ = angle3Pts0_180(starX, mid, ptZ);
    if((pt.x() - mid.x()) < 0.0f)
        angZ = 360.0f - angZ;

    // find X
    QVector3D starZ(mid.x(), mid.y(), mid.z() - 1);
    Angle backZ(0.0f, 0.0f, angZ);
    QVector3D rotatedPt = rotatePoint3FBack(pt, backZ.degToRad(), mid);
    float angX = angle3Pts0_180(rotatedPt, mid, starZ);
    if((rotatedPt.y() - mid.y()) < 0.0f)
        angX = 360.0f - angX;

    return Angle(angX, 0.0f, angZ);
}

QVector3D man::getCenter(std::vector<QVector3D> &contour)
{
    QVector3D center;
    if(contour.size() == 0) return center;
    for(size_t i = 0; i < contour.size(); i++)
        center += contour[i];
    center /= contour.size();
    return center;
}

bool man::isInContour(std::vector<Triangle> &tris, const QVector3D &pt)
{
    bool res = false;
    for(auto &tr : tris){
        res = isInTriangle(tr.toVector(), pt);
        if(res) return true;
    }
    return res;
}

bool man::isLineCross(const QVector3D &ptA, const QVector3D &ptB, const QVector3D &ptX, const QVector3D &ptY, QVector3D &cross)
{
    QVector3D p13, p43, p21;
    const double eps = 0.0001;
    double d1343, d4321, d1321, d4343, d2121;
    double numer, denom;

    p13.setX(ptA.x() - ptX.x());
    p13.setY(ptA.y() - ptX.y());
    p13.setZ(ptA.z() - ptX.z());
    p43.setX(ptY.x() - ptX.x());
    p43.setY(ptY.y() - ptX.y());
    p43.setZ(ptY.z() - ptX.z());
    if (std::abs(p43.x()) < eps && std::abs(p43.y()) < eps && std::abs(p43.z()) < eps)
        return false;
    p21.setX(ptB.x() - ptA.x());
    p21.setY(ptB.y() - ptA.y());
    p21.setZ(ptB.z() - ptA.z());
    if (std::abs(p21.x()) < eps && std::abs(p21.y()) < eps && std::abs(p21.z()) < eps)
        return false;

    d1343 = p13.x() * p43.x() + p13.y() * p43.y() + p13.z() * p43.z();
    d4321 = p43.x() * p21.x() + p43.y() * p21.y() + p43.z() * p21.z();
    d1321 = p13.x() * p21.x() + p13.y() * p21.y() + p13.z() * p21.z();
    d4343 = p43.x() * p43.x() + p43.y() * p43.y() + p43.z() * p43.z();
    d2121 = p21.x() * p21.x() + p21.y() * p21.y() + p21.z() * p21.z();

    denom = d2121 * d4343 - d4321 * d4321;
    if (std::abs(denom) < eps)
        return false;
    numer = d1343 * d4321 - d1321 * d4343;

    double mua, mub;
    mua = numer / denom;
    mub = (d1343 + d4321 * mua) / d4343;

    QVector3D pa, pb;
    pa.setX(ptA.x() + mua * p21.x());
    pa.setY(ptA.y() + mua * p21.y());
    pa.setZ(ptA.z() + mua * p21.z());
    pb.setX(ptX.x() + mub * p43.x());
    pb.setY(ptX.y() + mub * p43.y());
    pb.setZ(ptX.z() + mub * p43.z());

    const float precision = 0.01f;
    float crossDistance = pa.distanceToPoint(pb);
    if(crossDistance > precision) return false;

    cross = (pa + pb) / 2;
    if((mua >= 0.0 && mua <= 1.0) && (mub >= 0.0 && mub <= 1.0)) return true;
    else return false;
}

bool man::isCrossContour(const std::vector<QVector3D> &contour, const QVector3D &ptX, const QVector3D &ptY)
{ // TODO: IMPLEMENT man::isCrossContour
    /*bool res = false;
    for(size_t i = 0; i < contour.size(); i++){
        size_t nextInd = i + 1;
        if(nextInd == contour.size())
            nextInd = 0;
        // ---
        QVector3D A = contour[i];
        QVector3D B = contour[nextInd];
        // ---
        QVector3D cross;
        res = isLineCross(A, B, ptX, ptY, cross);
        if(res) return true;
    }
    return res;*/
}

void man::calcAddProperties(StlObject &object, bool isFull)
{
    calcSquare(object, isFull);
    calcVolume(object, isFull);
}

void man::calcSquare(StlObject &object, bool isFull)
{
    if(isFull){
        object.squareFull = 0.0f;
        for(const auto &tri : object.triangles)
            object.squareFull += squareTriangle(tri.vertex[0], tri.vertex[1], tri.vertex[2]);
    }
    else {
        object.squareCut = 0.0f;
        for(const auto &tri : object.triangles){
            if(tri.isGood)
                object.squareCut += squareTriangle(tri.vertex[0], tri.vertex[1], tri.vertex[2]);
        }
        for(const auto &ad : object.additional){
            if(ad.isGood)
                object.squareCut += squareTriangle(ad.vertex[0], ad.vertex[1], ad.vertex[2]);
        }
    }
}

void man::calcVolume(StlObject &object, bool isFull)
{ // TODO: IMPLEMENT man::calcVolume
    if(isFull){

    }
    else{

    }
}
