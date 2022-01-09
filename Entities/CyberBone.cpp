#include "CyberBone.h"

man::CyberBone::CyberBone()
{    
    material    = Material::Plastic;
    color       = colDarkBlue;
    colorCut    = colGrey;
    colorCut.a  = 10;
}

man::CyberBone::CyberBone(const QString & name, const QString &pathRel):
    CyberBone()
{
    this->name  = name;
    pathTo3DModelAbs = pathRel;
}

QMap<QString, QVariant> man::CyberBone::getPropertyList() const
{

}

void man::CyberBone::serialize(){
    std::cout << "Serialize CybBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
