#include "HumanBone.h"

man::HumanBone::HumanBone()
{
    isHuman = true;
}

man::HumanBone::HumanBone(const QString & name, const QString &pathRel){
    isHuman = true;
    this->name = name;
    pathTo3DModelRel = pathRel;
}

void man::HumanBone::serialize(){

}
