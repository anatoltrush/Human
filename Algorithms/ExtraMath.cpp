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
    float square = 0.0f;
    return square;
}
