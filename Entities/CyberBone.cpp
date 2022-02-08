#include "CyberBone.h"

man::CyberBone::CyberBone()
{    
    material    = Material::Plastic;
    color       = Qt::darkBlue;
    colorCut    = Qt::gray;
    colorHull   = colFuchsia;
    isExist     = false;
}

man::CyberBone::CyberBone(const QString & name, const QString &pathRel):
    CyberBone()
{
    this->name  = name;
    pathTo3DModelAbs = pathRel;
}

QMap<QString, QVariant> man::CyberBone::getPropertyList() const
{
    QMap<QString, QVariant> props = AbstractBone::getPropertyList();
    props["sep"] = "-";
    return props;
}

void man::CyberBone::serialize(){

}
