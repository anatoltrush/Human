#include "ExtraMath.h"

QVector3D man::rotatePoint3F(QVector3D point, const QVector3D &angleRad, QVector3D basePoint)
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

    float per = (ab + bc + ca) / 2;
    float sqrTriangle = sqrt(per * (per - ab) * (per - bc) * (per - ca));

    return sqrTriangle;
}

float man::squarePolygon(std::vector<QVector3D> &contour)
{
    // TODO: implement float man::squarePolygon(std::vector<man::Point3F> &contour)
    float square = 0.0f;
    return square;
}

bool man::isInContour(const std::vector<QVector3D> &contour, const QVector3D &pt)
{
    // float contSquare = squarePolygon(contour); // FIXME: change to squarePolygon()
    float contourSquare = squareTriangle(contour[0], contour[1], contour[2]);

    uint64_t partsSummSqr = 0;
    //float partsSummSqr = 0.0f; // ! error
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

    //contourSquare += 0.01f; // small add for float
    if(partsSummSqr > contourSquare)
        return false;
    else
        return true;
}

std::vector<QVector3D> man::makeUnique(const std::vector<QVector3D> &pts, float precision)
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
    resVec = makeUnique(resVec, precision);
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

float man::angle3Points(const QVector3D &pt0, QVector3D &pt1, const QVector3D &pt2, const QVector3D &planeNorm)
{
    QVector3D v1 = pt1 - pt0;
    QVector3D v2 = pt2 - pt1;

    QVector3D cross = QVector3D::crossProduct(v1, v2);
    float dot = QVector3D::dotProduct(v1, v2);

    float angle = std::atan2(cross.length(), dot);
    float test = QVector3D::dotProduct(planeNorm, cross);
    if (test < 0.0f)
        angle = M_PI_2 - angle;

    float degree = angle * 180.0f / M_PI;
    if (degree < 0.0f)
        degree += 360.0f;

    return degree;
}
