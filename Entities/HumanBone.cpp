#include "HumanBone.h"

man::HumanBone::HumanBone()
{
    material    = Material::HumanTissue;
    color       = colDarkGreen;
    colorCut    = colGrey;
    colorCut.a  = 10;
}

man::HumanBone::HumanBone(const QString & name, const QString &pathRel):
    HumanBone()
{
    this->name  = name;
    pathTo3DModelAbs = pathRel;
}

QMap<QString, QVariant> man::HumanBone::getPropertyList() const
{

}

void man::HumanBone::serialize(){

}
