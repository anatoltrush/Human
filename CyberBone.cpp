#include "CyberBone.h"

man::CyberBone::CyberBone()
{
    isHuman = false;
}

man::CyberBone::CyberBone(const QString & name){
    this->name = name;
    isHuman = false;
}

void man::CyberBone::serialize(){
    std::cout << "Serialize: " <<  name.toStdString() << std::endl; // NOTE: delete
}
