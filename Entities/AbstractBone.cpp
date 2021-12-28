#include "AbstractBone.h"

man::AbstractBone::AbstractBone()
{
    color.x = 0.0f;
    color.y = 0.75f;
    color.z = 1.0f;
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

void man::AbstractBone::setColor(int B, int G, int R)
{
    if(B > 255) B = 255;
    if(B < 0) B = 0;
    if(G > 255) G = 255;
    if(G < 0) G = 0;
    if(R > 255) R = 255;
    if(R < 0) R = 0;

    color.x = R / 255.0;
    color.y = G / 255.0;
    color.z = B / 255.0;
}

void man::AbstractBone::drawGLtriangle()
{
    for(size_t i = 0; i < stlObject.triangles.size(); i++){
        glBegin(GL_TRIANGLES);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(stlObject.triangles[i].vertex[0].x, stlObject.triangles[i].vertex[0].y, stlObject.triangles[i].vertex[0].z);
        glVertex3f(stlObject.triangles[i].vertex[1].x, stlObject.triangles[i].vertex[1].y, stlObject.triangles[i].vertex[1].z);
        glVertex3f(stlObject.triangles[i].vertex[2].x, stlObject.triangles[i].vertex[2].y, stlObject.triangles[i].vertex[2].z);
        glEnd();
    }
}

void man::AbstractBone::serialize()
{
    //std::cout << "Serialize AbsBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
