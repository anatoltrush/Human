#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#endif // PRIMITIVES_H

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

}
