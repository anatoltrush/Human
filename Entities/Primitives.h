#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>

#include <QString>

namespace man{

#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0f)

struct Point3F
{
    Point3F() {}
    Point3F(float _x, float _y, float _z):
    x(_x), y(_y), z(_z){}
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Point3F operator + (const Point3F &other){
        Point3F retPoint;
        retPoint.x = this->x + other.x;
        retPoint.y = this->y + other.y;
        retPoint.z = this->z + other.z;
        return retPoint;
    }

    Point3F operator - (const Point3F &other){
        Point3F retPoint;
        retPoint.x = this->x - other.x;
        retPoint.y = this->y - other.y;
        retPoint.z = this->z - other.z;
        return retPoint;
    }

    Point3F operator -= (const Point3F &other){
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Point3F operator += (const Point3F &other){
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Point3F degToRad(){
        Point3F retPoint;
        retPoint.x = DEG_TO_RAD(this->x);
        retPoint.y = DEG_TO_RAD(this->y);
        retPoint.z = DEG_TO_RAD(this->z);
        return retPoint;
    }
};

typedef Point3F Vertex;

typedef Point3F Color;

struct Triangle
{
    Triangle() {}

    Vertex vertex[3];
    Vertex normal;
    uint16_t attrByteCount = 0;
};

struct StlObject
{
    StlObject() {}

    QString objectName;

    std::vector<Triangle> triangles;

    float square = 0.0f;
    float volume = 0.0f;

    void clear()
    {
        objectName = "";
        triangles.clear();
    }
};

}

#endif // PRIMITIVES_H
