#include "HumanBone.h"

man::HumanBone::HumanBone()
{
    isHuman = true;
    material = Material::HumanTissue;
}

man::HumanBone::HumanBone(const QString & name, const QString &pathRel){
    isHuman = true;
    material = Material::HumanTissue;
    this->name = name;
    pathTo3DModelRel = pathRel;
}

void man::HumanBone::serialize(){

}
