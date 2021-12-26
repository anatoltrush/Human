#include "CyberBone.h"

man::CyberBone::CyberBone()
{
    isHuman = false;
    material = Material::Plastic;
}

man::CyberBone::CyberBone(const QString & name, const QString &pathRel){
    this->name = name;
    isHuman = false;
    pathTo3DModelRel = pathRel;
}

void man::CyberBone::serialize(){
    std::cout << "Serialize CybBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
