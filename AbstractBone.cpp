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
    pathTo3DModelAbs = pathTo3DModelRel + "/" + boneJsonObject[jsonFieldPath3D].toString();
}

void man::AbstractBone::defineChildren()
{
    QJsonArray childrenArray = boneJsonObject[jsonFieldChildren].toArray();
    for(const auto &child : childrenArray){
        QString childStr = child.toObject().value(jsonFieldName).toString();
        childrenStr.push_back(childStr);
    }
}

void man::AbstractBone::defineParents()
{
    std::cout << "defineParents " <<  name.toStdString() << std::endl; // NOTE: delete
}

void man::AbstractBone::calcNewBasePoint()
{
    std::cout << "calcNewBasePoint " <<  name.toStdString() << std::endl; // NOTE: delete
}

void man::AbstractBone::serialize()
{
    std::cout << "Serialize AbsBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
