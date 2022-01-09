#include "AbstractBone.h"

man::AbstractBone::AbstractBone()
{
    color       = colDeepSkyBlue;
    colorCut    = colGrey;
}

man::AbstractBone::~AbstractBone()
{
    std::cout << "-Delete AbsBone-" <<  name.toStdString() << std::endl; // NOTE: delete
}

void man::AbstractBone::fillProperties()
{
    // 3D
    pathTo3DModelAbs += "/" + boneJsonObject[jsonFieldPath3D].toString();
    // children
    QJsonArray childrenArray = boneJsonObject[jsonFieldChildren].toArray();
    for(const auto &child : childrenArray){
        QString chldName = child[jsonFieldName].toString();
        Point3F offsetPnt(child[QString("x")].toDouble(), child[QString("y")].toDouble(), child[QString("z")].toDouble());
        childrenPoints.insert(chldName, offsetPnt);
    }
    // parent
    QJsonObject parPoint = boneJsonObject[jsonFieldParent].toObject();
    parentOffset.x = parPoint["x"].toDouble();
    parentOffset.y = parPoint["y"].toDouble();
    parentOffset.z = parPoint["z"].toDouble();
    parentOffset.str = parPoint[jsonFieldName].toString();
    // rotation
    QJsonObject rotate = boneJsonObject[jsonFieldRotate].toObject();
    rotation.x = rotate["x"].toDouble();
    rotation.y = rotate["y"].toDouble();
    rotation.z = rotate["z"].toDouble();
}

void man::AbstractBone::rotateBone(const Point3F &basePoint, const Angle &angles)
{
    // children points
    for(auto &chlPt : childrenPoints)
        chlPt = rotatePoint3F(chlPt, angles.degToRad(), basePoint);

    // stl
    for(auto &tr : stlObject.triangles)
        for(auto &vr : tr.vertex)
            vr = rotatePoint3F(vr, angles.degToRad(), basePoint);
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

man::Point3F man::AbstractBone::getHighestPoint()
{
    Point3F highPt;
    for(const auto &tr : stlObject.triangles)
        for(const auto &vr : tr.vertex)
            if(vr.z > highPt.z) highPt = vr;
    return highPt;
}

man::Point3F man::AbstractBone::getLowestPoint()
{
    Point3F lowPt;
    for(const auto &tr : stlObject.triangles)
        for(const auto &vr : tr.vertex)
            if(vr.z < lowPt.z) lowPt = vr;
    return lowPt;
}

void man::AbstractBone::drawObjectGL() const
{
    glLineWidth(1.0f);
    for(size_t i = 0; i < stlObject.triangles.size(); i++){
        glBegin(GL_TRIANGLES);
        if(stlObject.triangles[i].isGood)
            glColor3ub(color.r, color.g, color.b);
        else
            glColor3ub(colorCut.r, colorCut.g, colorCut.b);
        glVertex3f(stlObject.triangles[i].vertex[0].x, stlObject.triangles[i].vertex[0].y, stlObject.triangles[i].vertex[0].z);
        glVertex3f(stlObject.triangles[i].vertex[1].x, stlObject.triangles[i].vertex[1].y, stlObject.triangles[i].vertex[1].z);
        glVertex3f(stlObject.triangles[i].vertex[2].x, stlObject.triangles[i].vertex[2].y, stlObject.triangles[i].vertex[2].z);
        glEnd();
    }
    if(basePoint){
        QMap<QString, Point3F>::const_iterator chlPt;
        for(chlPt = childrenPoints.begin(); chlPt != childrenPoints.end(); chlPt++){
            glLineWidth(2.0f);
            glBegin(GL_LINES);
            glColor3ub(colGoldenRod.r, colGoldenRod.g, colGoldenRod.b);
            glVertex3f(basePoint->x, basePoint->y, basePoint->z);
            glVertex3f(chlPt.value().x, chlPt.value().y, chlPt.value().z);
            glEnd();
        }
        for(size_t i = 0; i < interSects.size(); i++){
            glPointSize(6.0f);
            glBegin(GL_POINTS);
            glVertex3f(interSects[i].x, interSects[i].y, interSects[i].z);
            glEnd();
        }
    }
}

void man::AbstractBone::drawBasePoint() const
{
    if(!basePoint) return;

    glLineWidth(2.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(colDarkRed.r, colDarkRed.g, colDarkRed.b);
    glVertex3f(basePoint->x - 1, basePoint->y, basePoint->z + 1);
    glVertex3f(basePoint->x + 1, basePoint->y, basePoint->z + 1);
    glVertex3f(basePoint->x, basePoint->y, basePoint->z - 1);
    glEnd();
}

QMap<QString, QVariant> man::AbstractBone::getPropertyList() const
{

}

void man::AbstractBone::serialize()
{
    //std::cout << "Serialize AbsBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
