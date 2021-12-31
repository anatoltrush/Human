#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>

#include <QString>

namespace man{

struct Point3F
{
    Point3F() {}
    Point3F(float _x, float _y, float _z):
    x(_x), y(_y), z(_z){}
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
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
