#include "CyberBone.h"

man::CyberBone::CyberBone()
{
    isHuman = false;
    material = Material::Plastic;
}

man::CyberBone::CyberBone(const QString & name, const QString &pathRel){
    isHuman = false;
    material = Material::Plastic;
    this->name = name;    
    pathTo3DModelRel = pathRel;
}

QMap<QString, QVariant> man::CyberBone::getPropertyList() const
{

}

void man::CyberBone::serialize(){
    std::cout << "Serialize CybBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
