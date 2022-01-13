#ifndef EXTRAMATH_H
#define EXTRAMATH_H

#include "Entities/Primitives.h"

namespace man{

    Point3F rotatePoint3F(Point3F point, const Point3F &angleRad, Point3F basePoint);

    Point3F rotatePoint3FX(Point3F point, const float &angX);
    Point3F rotatePoint3FY(Point3F point, const float &angY);
    Point3F rotatePoint3FZ(Point3F point, const float &angZ);

    float distance(const Point3F &ptA, const Point3F &ptB);
    float squareTriangle(const Point3F &A, const Point3F &B, const Point3F &C);
    float squarePolygon(std::vector<Point3F> &contour);

    bool isInContour(const std::vector<Point3F> &contour, const Point3F &pt);
    std::vector<Point3F> makeUnique(const std::vector<Point3F> &pts, float precision);
    std::vector<Point3F> getPtsFromTris(const std::vector<Triangle>& tris, float precision);
}

#endif // EXTRAMATH_H
