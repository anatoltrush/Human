#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>

#include <QString>

namespace man{

#define DEG_TO_RAD(deg) ((deg) * M_PI / 180.0f)

struct Point3F
{
    Point3F() {}
    Point3F(float X, float Y, float Z):
    x(X), y(Y), z(Z){}
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
};

struct Point3FStr : Point3F
{
    Point3FStr() {}
    QString str;

    Point3F toPoint3F(){
        return Point3F(this->x, this->y, this->z);
    }
};

struct Angle : Point3F
{
    Angle() {}

    Angle degToRad() const {
        Angle retPoint;
        retPoint.x = DEG_TO_RAD(this->x);
        retPoint.y = DEG_TO_RAD(this->y);
        retPoint.z = DEG_TO_RAD(this->z);
        return retPoint;
    }
};

typedef Point3F Vertex;

struct Color4ub
{
    Color4ub() {}
    Color4ub(uint8_t R, uint8_t G, uint8_t B, uint8_t A = 255):
    r(R), g(G), b(B), a(A){}

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
};

struct Triangle
{
    Triangle() {}

    Vertex vertex[3];
    Vertex normal;
    uint16_t attrByteCount = 0;

    bool isExist = true;
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
