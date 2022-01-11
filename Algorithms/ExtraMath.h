#ifndef EXTRAMATH_H
#define EXTRAMATH_H

#include "Entities/Primitives.h"

namespace man{

    Point3F rotatePoint3F(Point3F point, const Point3F &angleRad, Point3F basePoint);

    Point3F rotatePoint3FX(Point3F point, const float &angX);
    Point3F rotatePoint3FY(Point3F point, const float &angY);
    Point3F rotatePoint3FZ(Point3F point, const float &angZ);

    float distance(const Point3F &ptA, const Point3F &ptB);
}

#endif // EXTRAMATH_H
