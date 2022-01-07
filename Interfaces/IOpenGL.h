#ifndef IOPENGL_H
#define IOPENGL_H

#include "Config/Colors.h"

namespace man{

class IOpenGL
{
public:
    IOpenGL() = default;
    virtual ~IOpenGL() = default;

    Color4ub color = Color4ub(1.0f, 0.0f, 0.0f);

    virtual void drawObjectGL() const = 0;

    void setColor(uint8_t B, uint8_t G, uint8_t R, uint8_t A = 255)
    {
        color.r = R;
        color.g = G;
        color.b = B;
        color.a = A;
    }
};

}

#endif // IOPENGL_H
