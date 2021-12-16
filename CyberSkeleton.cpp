#include "CyberSkeleton.h"

man::CyberSkeleton::CyberSkeleton()
{
    bones.insert(std::pair<std::string_view, CyberBone>(boneHead, CyberBone(boneHead)));    
    bones.insert(std::pair<std::string_view, CyberBone>(boneSpine, CyberBone(boneSpine)));
    bones.insert(std::pair<std::string_view, CyberBone>(boneHandR, CyberBone(boneHandR)));
    bones.insert(std::pair<std::string_view, CyberBone>(boneHandL, CyberBone(boneHandL)));
    bones.insert(std::pair<std::string_view, CyberBone>(boneLerR, CyberBone(boneLerR)));
    bones.insert(std::pair<std::string_view, CyberBone>(boneLegL, CyberBone(boneLegL)));

    bones[boneHead].children.push_back(&bones[boneSpine]);
    bones[boneSpine].children.push_back(&bones[boneHandR]);
    bones[boneSpine].children.push_back(&bones[boneHandL]);
    bones[boneSpine].children.push_back(&bones[boneLerR]);
    bones[boneSpine].children.push_back(&bones[boneLegL]);
}

void man::CyberSkeleton::loadFromJson(){

}
