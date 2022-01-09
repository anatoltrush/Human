#ifndef CUTSURFACE_H
#define CUTSURFACE_H

#include <GL/gl.h>

#include "Entities/AbstractSkeleton.h"

namespace man{

class CutSurface : public IOpenGL, public IProperty
{
public:
    CutSurface();

    mutable Point3F center;
    Triangle surface;
    Point4F equal;

    void execute(AbstractSkeleton* skeleton);

    virtual void drawObjectGL() const override;

    virtual QMap<QString, QVariant> getPropertyList() const override;

private:
    bool isIntersect(const Point3F &ptBeg, Point3F &ptInter, Point3F &ptEnd);

    void cutAllLower(AbstractBone* startBone, bool isHuman);
    void cutSingleLower(AbstractBone* startBone, bool isHuman);

    Point3F vectorProduct(const Point3F &A, const Point3F &B);
    float dotProduct(const Point3F &A, const Point3F &B);

    void calcCenter() const;
    void calcPlaneEquation();

    float applyEqual(const Point3F &pt);
};

}

#endif // CUTSURFACE_H
