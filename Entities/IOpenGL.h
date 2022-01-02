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

    virtual void setColor(uint8_t B, uint8_t G, uint8_t R) = 0;
};

}

#endif // IOPENGL_H
