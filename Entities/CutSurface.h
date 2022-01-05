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

};

}

#endif // CUTSURFACE_H
