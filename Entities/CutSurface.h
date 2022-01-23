#ifndef CUTSURFACE_H
#define CUTSURFACE_H

#include <QVector2D>
#include <QMultiMap>

#include "Entities/AbstractSkeleton.h"

namespace man{

class CutSurface : public IOpenGL, public IProperty
{
public:
    CutSurface();

    QVector3D planeCenter;
    Triangle planeSurface;
    QVector4D planeEqual;

    void execute(AbstractSkeleton* skeleton, bool &isWarning);

    virtual void drawObjectGL() override;

    virtual QMap<QString, QVariant> getPropertyList() const override;

private:
    bool isIntersect(const QVector3D &ptBeg, QVector3D &ptInter, QVector3D &ptEnd);

    void cutAllLower(AbstractBone* startBone, bool isHuman);
    void cutSingleLower(AbstractBone* bone, bool isHuman);
    std::vector<Triangle> makePlug(std::vector<QVector3D> &pts);

    float applyEqual(const QVector3D &pt);
    void smoothContour(std::vector<Triangle> &triangles, std::vector<QVector3D> &contour, const QVector3D &center);
};

}

#endif // CUTSURFACE_H
