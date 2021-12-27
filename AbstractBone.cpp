#include "AbstractBone.h"

man::AbstractBone::AbstractBone()
{

}

man::AbstractBone::~AbstractBone()
{
    std::cout << "-Delete AbsBone-" <<  name.toStdString() << std::endl; // NOTE: delete
}

void man::AbstractBone::fillProperties()
{
    // 3D
    pathTo3DModelAbs = pathTo3DModelRel + "/" + boneJsonObject[jsonFieldPath3D].toString();
    // children
    QJsonArray childrenArray = boneJsonObject[jsonFieldChildren].toArray();
    for(const auto &child : childrenArray){
        childrenStr.push_back(child.toString());
    }
    // offsets
    QJsonObject anchorPoint = boneJsonObject[jsonFieldAnchor].toObject();
    offsetBase.x = anchorPoint["x"].toDouble();
    offsetBase.y = anchorPoint["y"].toDouble();
    offsetBase.z = anchorPoint["z"].toDouble();
}

void man::AbstractBone::applyRotation()
{

}

void man::AbstractBone::applyOffsets()
{
    for(auto &tr : stlObject.triangles){
        for(int i = 0; i < 3; i++){
            tr.vertex[i].x += offsetBase.x;
            tr.vertex[i].y += offsetBase.y;
            tr.vertex[i].z += offsetBase.z;
        }
    }
}

void man::AbstractBone::serialize()
{
    //std::cout << "Serialize AbsBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
