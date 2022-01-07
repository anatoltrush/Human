#include "CutSurface.h"

man::CutSurface::CutSurface()
{
    setColor(180, 105, 245); // pink

    triangle.vertex[0] = Point3F(-120.0f, 100.0f, -80.0f); // NOTE: delete
    triangle.vertex[1] = Point3F(120.0f, 100.0f, -60.0f);
    triangle.vertex[2] = Point3F(0.0f, -120.0f, -40.0f);
}

void man::CutSurface::drawObjectGL() const
{
    glLineWidth(5.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(color.r, color.g, color.b);
    glVertex3f(triangle.vertex[0].x, triangle.vertex[0].y, triangle.vertex[0].z);
    glVertex3f(triangle.vertex[1].x, triangle.vertex[1].y, triangle.vertex[1].z);
    glVertex3f(triangle.vertex[2].x, triangle.vertex[2].y, triangle.vertex[2].z);
    glEnd();
}

QMap<QString, QVariant> man::CutSurface::getPropertyList() const
{

}
