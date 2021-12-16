#include "HumanSkeleton.h"

man::HumanSkeleton::HumanSkeleton()
{
    bones.insert(std::pair<std::string_view, HumanBone>(boneHead, HumanBone(boneHead)));
    bones.insert(std::pair<std::string_view, HumanBone>(boneSpine, HumanBone(boneSpine)));
    bones.insert(std::pair<std::string_view, HumanBone>(boneHandR, HumanBone(boneHandR)));
    bones.insert(std::pair<std::string_view, HumanBone>(boneHandL, HumanBone(boneHandL)));
    bones.insert(std::pair<std::string_view, HumanBone>(boneLerR, HumanBone(boneLerR)));
    bones.insert(std::pair<std::string_view, HumanBone>(boneLegL, HumanBone(boneLegL)));
}

void man::HumanSkeleton::loadFromJson(){

}
