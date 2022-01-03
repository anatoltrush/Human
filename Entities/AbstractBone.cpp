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
        QString chldName = child[jsonFieldName].toString();
        Point3F offsetPnt(child[QString("x")].toDouble(), child[QString("y")].toDouble(), child[QString("z")].toDouble());
        childrenPoints.insert(chldName, offsetPnt);
    }
    // parent
    QJsonObject parPoint = boneJsonObject[jsonFieldParent].toObject();
    parentOffsetPoint.x = parPoint["x"].toDouble();
    parentOffsetPoint.y = parPoint["y"].toDouble();
    parentOffsetPoint.z = parPoint["z"].toDouble();
    parentName = parPoint[jsonFieldName].toString();
    // rotation
    QJsonObject rotate = boneJsonObject[jsonFieldRotate].toObject();
    rotation.x = rotate["x"].toDouble();
    rotation.y = rotate["y"].toDouble();
    rotation.z = rotate["z"].toDouble();
}

void man::AbstractBone::applyRotation()
{

}

void man::AbstractBone::applyOffsets(const Point3F &offset)
{
    for(auto &chP : childrenPoints){
        chP.x += offset.x;
        chP.y += offset.y;
        chP.z += offset.z;
    }
    // -----
    for(auto &tr : stlObject.triangles){
        for(int i = 0; i < 3; i++){
            tr.vertex[i].x += offset.x;
            tr.vertex[i].y += offset.y;
            tr.vertex[i].z += offset.z;
        }
    }
}

void man::AbstractBone::setColor(uint8_t B, uint8_t G, uint8_t R)
{
    color.x = R / 255.0f;
    color.y = G / 255.0f;
    color.z = B / 255.0f;
}

void man::AbstractBone::drawObjectGL() const
{
    glLineWidth(1.0f);
    for(size_t i = 0; i < stlObject.triangles.size(); i++){
        glBegin(GL_TRIANGLES);
        glColor3f(color.x, color.y, color.z);
        glVertex3f(stlObject.triangles[i].vertex[0].x, stlObject.triangles[i].vertex[0].y, stlObject.triangles[i].vertex[0].z);
        glVertex3f(stlObject.triangles[i].vertex[1].x, stlObject.triangles[i].vertex[1].y, stlObject.triangles[i].vertex[1].z);
        glVertex3f(stlObject.triangles[i].vertex[2].x, stlObject.triangles[i].vertex[2].y, stlObject.triangles[i].vertex[2].z);
        glEnd();
    }
}

void man::AbstractBone::drawBasePoint() const
{
    if(!basePoint) return;

    Color colRed(0.8f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(colRed.x, colRed.y, colRed.z);
    glVertex3f(basePoint->x - 1, basePoint->y, basePoint->z + 1);
    glVertex3f(basePoint->x + 1, basePoint->y, basePoint->z + 1);
    glVertex3f(basePoint->x, basePoint->y, basePoint->z - 1);
    glEnd();
}

void man::AbstractBone::serialize()
{
    //std::cout << "Serialize AbsBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
