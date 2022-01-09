#ifndef IOPENGL_H
#define IOPENGL_H

#include "Config/Colors.h"

namespace man{

class IOpenGL
{
public:
    IOpenGL() = default;
    virtual ~IOpenGL() = default;

    Color4ub color      = colBlack;
    Color4ub colorCut   = colGrey;

    virtual void drawObjectGL() const = 0;

};

}

#endif // IOPENGL_H
