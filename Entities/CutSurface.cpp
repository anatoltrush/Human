#include "CutSurface.h"

man::CutSurface::CutSurface()
{

}

void man::CutSurface::drawObjectGL() const
{

}

void man::CutSurface::setColor(uint8_t B, uint8_t G, uint8_t R)
{
    color.x = R / 255.0f;
    color.y = G / 255.0f;
    color.z = B / 255.0f;
}
