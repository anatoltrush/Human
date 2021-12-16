#include "CyberBone.h"

man::CyberBone::CyberBone()
{
    isHuman = false;
}

man::CyberBone::CyberBone(const std::string_view & name){
    this->name = name;
    isHuman = false;
}

void man::CyberBone::serialize(){
    std::cout << "Serialize: " <<  name << std::endl; // NOTE: delete
}
