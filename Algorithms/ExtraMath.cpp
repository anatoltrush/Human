#include "ExtraMath.h"

man::Point3F man::rotatePoint3F(Point3F point, const Point3F &angleRad, Point3F basePoint)
{
    Point3F diffPt = point - basePoint;
    Point3F aftXrot = rotatePoint3FX(diffPt, angleRad.x);
    Point3F aftYrot = rotatePoint3FY(aftXrot, angleRad.y);
    Point3F aftZrot = rotatePoint3FZ(aftYrot, angleRad.z);

    aftZrot += basePoint;
    return aftZrot;
}

man::Point3F man::rotatePoint3FX(Point3F point, const float &angX)
{
    Point3F resPoint;
    resPoint.x = point.x;
    resPoint.y = point.y * cos(angX) - point.z * sin(angX);
    resPoint.z = point.y * sin(angX) + point.z * cos(angX);
    return resPoint;
}

man::Point3F man::rotatePoint3FY(Point3F point, const float &angY)
{
    Point3F resPoint;
    resPoint.x = point.x * cos(angY) + point.z * sin(angY);
    resPoint.y = point.y;
    resPoint.z = -point.x * sin(angY) + point.z * cos(angY);
    return resPoint;
}

man::Point3F man::rotatePoint3FZ(Point3F point, const float &angZ)
{
    Point3F resPoint;
    resPoint.x = point.x * cos(angZ) - point.y * sin(angZ);
    resPoint.y = point.x * sin(angZ) + point.y * cos(angZ);
    resPoint.z = point.z;
    return resPoint;
}

float man::distance(const man::Point3F &ptA, const man::Point3F &ptB)
{
    return sqrt((ptB.x - ptA.x) * (ptB.x - ptA.x)
                + (ptB.y - ptA.y) * (ptB.y - ptA.y)
                + (ptB.z - ptA.z) * (ptB.z - ptA.z));
}

float man::squareTriangle(const man::Point3F &A, const man::Point3F &B, const man::Point3F &C)
{
    float ab = distance(A, B);
    float bc = distance(B, C);
    float ca = distance(C, A);

    float per = (ab + bc + ca) / 2;
    float sqrTriangle = sqrt(per * (per - ab) * (per - bc) * (per - ca));

    return sqrTriangle;
}

float man::squarePolygon(std::vector<man::Point3F> &contour)
{
    // TODO: implement float man::squarePolygon(std::vector<man::Point3F> &contour)
    float square = 0.0f;
    return square;
}

bool man::isInContour(const std::vector<man::Point3F> &contour, const Point3F &pt)
{
    // float contSquare = squarePolygon(contour); // FIXME: change to squarePolygon()
    float contourSquare = squareTriangle(contour[0], contour[1], contour[2]);

    uint64_t partsSummSqr = 0;
    //float partsSummSqr = 0.0f; // ! error
    for(size_t i = 0; i < contour.size(); i++){
        size_t nextInd = i + 1;
        if(nextInd == contour.size())
            nextInd = 0;

        Point3F A = contour[i];
        Point3F B = pt;
        Point3F C = contour[nextInd];

        float triSqare = squareTriangle(A, B, C);
        partsSummSqr += triSqare;
    }

    //contourSquare += 0.01f; // small add for float
    if(partsSummSqr > contourSquare)
        return false;
    else
        return true;
}

std::vector<man::Point3F> man::makeUnique(const std::vector<man::Point3F> &pts, float precision)
{
    std::vector<Point3F> unique = pts;
    for(size_t i = 0; i < unique.size(); i++){
        for(size_t j = 0; j < unique.size(); j++){
            if(i == j) continue;
            float dist = distance(unique[i], unique[j]);
            if(dist < precision){
                unique.erase(unique.begin() + i);
                i--;
            }
        }
    }
    return unique;
}

std::vector<man::Point3F> man::getPtsFromTris(const std::vector<man::Triangle> &tris, float precision)
{
    std::vector<Point3F>resVec;
    for(const auto &tr : tris){
        resVec.push_back(tr.vertex[0]);
        resVec.push_back(tr.vertex[1]);
        resVec.push_back(tr.vertex[2]);
    }
    // ---
    resVec = makeUnique(resVec, precision);
    return resVec;
}
