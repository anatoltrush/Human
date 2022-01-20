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

    mutable QVector3D center;
    Triangle surface;
    QVector4D equal;

    void execute(AbstractSkeleton* skeleton, bool &isWarning);

    virtual void drawObjectGL() const override;

    virtual QMap<QString, QVariant> getPropertyList() const override;

private:
    bool isIntersect(const QVector3D &ptBeg, QVector3D &ptInter, QVector3D &ptEnd);

    void cutAllLower(AbstractBone* startBone, bool isHuman);
    void cutSingleLower(AbstractBone* bone, bool isHuman);
    std::vector<Triangle> makePlug(std::vector<QVector3D> &pts);

    float dotProduct(const QVector3D &A, const QVector3D &B); // FIXME: delete

    void calcCenter() const;
    float applyEqual(const QVector3D &pt);
};

}

#endif // CUTSURFACE_H
