#ifndef CUTSURFACE_H
#define CUTSURFACE_H

#include <GL/gl.h>

#include "Interfaces/IOpenGL.h"
#include "Interfaces/IProperty.h"
#include "Entities/Primitives.h"

namespace man{

class CutSurface : public IOpenGL, public IProperty
{
public:
    CutSurface();

    Angle angle;

    Triangle triangle;

    virtual void drawObjectGL() const override;

    virtual QMap<QString, QVariant> getPropertyList() const override;
};

}

#endif // CUTSURFACE_H
