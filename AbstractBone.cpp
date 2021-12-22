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
    ptOffset.x = anchorPoint["x"].toDouble();
    ptOffset.y = anchorPoint["y"].toDouble();
    ptOffset.z = anchorPoint["z"].toDouble();
}

void man::AbstractBone::calcNewBasePoint()
{
    std::cout << "calcNewBasePoint " <<  name.toStdString() << std::endl; // NOTE: delete
}

void man::AbstractBone::serialize()
{
    std::cout << "Serialize AbsBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
