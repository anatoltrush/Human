#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include <math.h>

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

    virtual Point3F operator + (const Point3F &other){
        Point3F retPoint;
        retPoint.x = this->x + other.x;
        retPoint.y = this->y + other.y;
        retPoint.z = this->z + other.z;
        return retPoint;
    }

    virtual Point3F operator - (const Point3F &other){
        Point3F retPoint;
        retPoint.x = this->x - other.x;
        retPoint.y = this->y - other.y;
        retPoint.z = this->z - other.z;
        return retPoint;
    }

    virtual Point3F operator / (float div){
        Point3F retPoint;
        retPoint.x = this->x / div;
        retPoint.y = this->y / div;
        retPoint.z = this->z / div;
        return retPoint;
    }

    virtual Point3F operator -= (const Point3F &other){
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    virtual Point3F operator += (const Point3F &other){
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    virtual Point3F operator *= (const Point3F &other){
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        return *this;
    }

    virtual Point3F operator /= (float div){
        this->x /= div;
        this->y /= div;
        this->z /= div;
        return *this;
    }

    virtual Point3F operator *= (float mult){
        this->x *= mult;
        this->y *= mult;
        this->z *= mult;
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

struct Point4F : Point3F
{
    Point4F() {}
    Point4F(const Point3F &pt){
        x = pt.x;
        y = pt.y;
        z = pt.z;
    }

    float d = 0.0f;
};

struct Angle : Point3F
{
    Angle() {}
    Angle(float X, float Y, float Z):
        Point3F(X, Y, Z){}

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
    Triangle() {
        contour.clear();
    }
    Triangle(const Vertex &zero, const Vertex &one, const Vertex &two,
             const Vertex &norm, bool isGood){
        vertex[0] = zero;
        vertex[1] = one;
        vertex[2] = two;
        normal = norm;
        this->isGood = isGood;
        contour.clear();
    }

    const std::vector<Point3F>& toVector(){
        contour.clear();
        for(int i = 0; i < 3; i++)
            contour.push_back(vertex[i]);
        return contour;
    }

    Vertex vertex[3];
    Vertex normal;
    uint16_t attrByteCount = 0;

    bool isGood = true;

private:
    std::vector<Point3F> contour;
};

struct StlObject
{
    StlObject() {}

    QString objectName;

    std::vector<Triangle> triangles;
    std::vector<Triangle> additional;

    float square = 0.0f;
    float volume = 0.0f;

    void clear()
    {
        objectName = "";
        triangles.clear();
        additional.clear();
        square = 0.0f;
        volume = 0.0f;
    }
};

}

#endif // PRIMITIVES_H
