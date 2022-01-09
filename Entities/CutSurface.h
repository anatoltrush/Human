#ifndef CUTSURFACE_H
#define CUTSURFACE_H

#include <GL/gl.h>

#include "Entities/AbstractSkeleton.h"

namespace man{

class CutSurface : public IOpenGL, public IProperty
{
public:
    CutSurface();

    Angle angle;
    mutable Point3F center;
    Triangle surface;

    void apply(AbstractSkeleton* skeleton);

    virtual void drawObjectGL() const override;

    virtual QMap<QString, QVariant> getPropertyList() const override;

private:
    bool isIntersect(const Point3F &ptBeg, Point3F &ptInter, Point3F &ptEnd);

    void cutAllLower(AbstractBone* startBone, bool isHuman);

    Point3F vectorProduct(const Point3F &A, const Point3F &B);
    float dotProduct(const Point3F &A, const Point3F &B);

    void calcCenter() const;
};

}

#endif // CUTSURFACE_H
