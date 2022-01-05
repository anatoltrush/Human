#ifndef IOPENGL_H
#define IOPENGL_H

#include "Entities/Primitives.h"

namespace man{

class IOpenGL
{
public:
    IOpenGL() = default;
    virtual ~IOpenGL() = default;

    Color color = Color(1.0f, 0.0f, 0.0f);

    virtual void drawObjectGL() const = 0;

    void setColor(uint8_t B, uint8_t G, uint8_t R)
    {
        color.x = R / 255.0f;
        color.y = G / 255.0f;
        color.z = B / 255.0f;
    }
};

}

#endif // IOPENGL_H
