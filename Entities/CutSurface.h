#ifndef CUTSURFACE_H
#define CUTSURFACE_H

#include <GL/gl.h>

#include "IOpenGL.h"

namespace man{

class CutSurface : public IOpenGL
{
public:
    CutSurface();

    virtual void drawObjectGL() const override;

    virtual void setColor(uint8_t B, uint8_t G, uint8_t R) override;
};

}

#endif // CUTSURFACE_H
