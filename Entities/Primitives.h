#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include <math.h>

#include <QString>
#include <QVector3D>
#include <QVector4D>

namespace man{

#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0f)

struct Point3FStr : public QVector3D
{
public:
    Point3FStr() {}
    QString str;

    QVector3D toPoint3F(){
        return QVector3D(this->x(), this->y(), this->z());
    }
};

struct Angle : public QVector3D
{
public:
    Angle() {}
    Angle(float X, float Y, float Z):
        QVector3D(X, Y, Z){}

    Angle degToRad() const {
        Angle retPoint;
        retPoint.setX(DEG_TO_RAD(this->x()));
        retPoint.setY(DEG_TO_RAD(this->y()));
        retPoint.setZ(DEG_TO_RAD(this->z()));
        return retPoint;
    }
};

struct Line
{
    Line() {}
    QVector3D ptBeg;
    QVector3D ptEnd;
};

struct Triangle
{
    Triangle() {
        contour.clear();
    }
    Triangle(const QVector3D &zero, const QVector3D &one, const QVector3D &two,
             const QVector3D &norm, bool isGood){
        vertex[0] = zero;
        vertex[1] = one;
        vertex[2] = two;
        normal = norm;
        this->isGood = isGood;
        contour.clear();
    }

    std::vector<QVector3D>& toVector(){
        contour.clear();
        for(int i = 0; i < 3; i++)
            contour.push_back(vertex[i]);
        return contour;
    }

    QVector3D vertex[3];
    QVector3D normal;
    uint16_t attrByteCount = 0;

    bool isGood = true;

private:
    std::vector<QVector3D> contour;
};

struct StlObject
{
    StlObject() {}

    QString objectName;

    std::vector<Triangle> triangles;
    std::vector<Triangle> additional;

    float square = 0.0f;
    float volume = 0.0f;

    void clear(){
        objectName = "";
        triangles.clear();
        additional.clear();
        square = 0.0f;
        volume = 0.0f;
    }
};

}

#endif // PRIMITIVES_H
