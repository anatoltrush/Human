#ifndef EXTRAMATH_H
#define EXTRAMATH_H

#include "Entities/Primitives.h"

namespace man{
    QVector3D rotatePoint3F(QVector3D point, const QVector3D &angleRad, QVector3D basePoint);

    QVector3D rotatePoint3FX(QVector3D point, const float &angX);
    QVector3D rotatePoint3FY(QVector3D point, const float &angY);
    QVector3D rotatePoint3FZ(QVector3D point, const float &angZ);

    float squareTriangle(const QVector3D &A, const QVector3D &B, const QVector3D &C);
    float squarePolygon(std::vector<QVector3D> &contour);

    bool isInTriangle(const std::vector<QVector3D> &contour, const QVector3D &pt);
    bool isInContour(std::vector<Triangle> &tris, const QVector3D &pt);

    bool isLineCross(const QVector3D &ptA, const QVector3D &ptB, const QVector3D &ptX, const QVector3D &ptY, QVector3D &cross);
    bool isCrossContour(const std::vector<QVector3D> &contour, const QVector3D &ptX, const QVector3D &ptY);

    std::vector<QVector3D> makeUniquePts(const std::vector<QVector3D> &pts, float precision);
    std::vector<QVector3D> getPtsFromTris(const std::vector<Triangle>& tris, float precision);

    QVector3D vectorProduct(const QVector3D &A, const QVector3D &B);
    QVector4D calcPlaneEquation(const QVector3D &pt0, QVector3D &pt1, const QVector3D &pt2);

    float angle3Pts0_180(const QVector3D &pt0, QVector3D &pt1, const QVector3D &pt2);
    QVector3D getCenter(std::vector<QVector3D> &contour);
}

#endif // EXTRAMATH_H
