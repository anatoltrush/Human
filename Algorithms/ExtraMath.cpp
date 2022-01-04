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
