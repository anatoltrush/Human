#include "HumanBone.h"

man::HumanBone::HumanBone()
{
    isHuman = true;
}

man::HumanBone::HumanBone(const QString & name){
    isHuman = true;
    this->name = name;
}

void man::HumanBone::serialize(){

}
