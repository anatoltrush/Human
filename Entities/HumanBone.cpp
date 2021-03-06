#include "HumanBone.h"

man::HumanBone::HumanBone()
{
    material    = Material::HumanTissue;
    color       = Qt::darkGreen;
    colorCut    = Qt::gray;
    colorHull   = colGoldenRod;
    isExist     = true;
}

man::HumanBone::HumanBone(const QString & name, const QString &pathRel):
    HumanBone()
{
    this->name  = name;
    pathTo3DModelAbs = pathRel;
}

QMap<QString, QVariant> man::HumanBone::getPropertyList() const
{
    QMap<QString, QVariant> props;
    props["HumanBone"] = "<-HumanBone->";
    return props;
}

void man::HumanBone::serialize(){

}
