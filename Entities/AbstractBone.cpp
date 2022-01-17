#include "AbstractBone.h"

man::AbstractBone::AbstractBone()
{
    color       = Qt::cyan;
    colorCut    = Qt::gray;
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
    for(const auto &child : qAsConst(childrenArray)){
        QString chldName = child.toObject()[jsonFieldName].toString();
        QVector3D offsetPnt(child.toObject()[QString("x")].toDouble(),
                child.toObject()[QString("y")].toDouble(),
                child.toObject()[QString("z")].toDouble());
        childrenPoints.insert(chldName, offsetPnt);
    }
    // parent
    QJsonObject parPoint = boneJsonObject[jsonFieldParent].toObject();
    parentOffset.setX(parPoint["x"].toDouble());
    parentOffset.setY(parPoint["y"].toDouble());
    parentOffset.setZ(parPoint["z"].toDouble());
    parentOffset.str = parPoint[jsonFieldName].toString();
    // rotation
    QJsonObject rotate = boneJsonObject[jsonFieldRotate].toObject();
    rotation.setX(rotate["x"].toDouble());
    rotation.setY(rotate["y"].toDouble());
    rotation.setZ(rotate["z"].toDouble());
}

void man::AbstractBone::rotateBone(const QVector3D &basePoint, const Angle &angles)
{
    // children points
    for(auto &chlPt : childrenPoints)
        chlPt = rotatePoint3F(chlPt, angles.degToRad(), basePoint);

    // stl
    for(auto &tr : stlObject.triangles)
        for(auto &vr : tr.vertex)
            vr = rotatePoint3F(vr, angles.degToRad(), basePoint);
}

void man::AbstractBone::applyOffsets(const QVector3D &offset)
{
    for(auto &chP : childrenPoints)
        chP += offset;
    // -----
    for(auto &tr : stlObject.triangles)
        for(int i = 0; i < 3; i++)
            tr.vertex[i] += offset;
}

QVector3D man::AbstractBone::getHighestPoint()
{
    QVector3D highPt;
    for(const auto &tr : stlObject.triangles)
        for(const auto &vr : tr.vertex)
            if(vr.z() > highPt.z())
                highPt = vr;
    return highPt;
}

QVector3D man::AbstractBone::getLowestPoint()
{
    QVector3D lowPt;
    for(const auto &tr : stlObject.triangles)
        for(const auto &vr : tr.vertex)
            if(vr.z() < lowPt.z())
                lowPt = vr;
    return lowPt;
}

void man::AbstractBone::drawObjectGL() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1.0f);
    for(size_t i = 0; i < stlObject.triangles.size(); i++){
        glBegin(GL_TRIANGLES);
        if(stlObject.triangles[i].isGood){
            glColor3ub(color.red(), color.green(), color.blue());
            glVertex3f(stlObject.triangles[i].vertex[0].x(), stlObject.triangles[i].vertex[0].y(), stlObject.triangles[i].vertex[0].z());
            glVertex3f(stlObject.triangles[i].vertex[1].x(), stlObject.triangles[i].vertex[1].y(), stlObject.triangles[i].vertex[1].z());
            glVertex3f(stlObject.triangles[i].vertex[2].x(), stlObject.triangles[i].vertex[2].y(), stlObject.triangles[i].vertex[2].z());
        }
        glEnd();
    }
    /*for(size_t i = 0; i < stlObject.triangles.size(); i++){
        glBegin(GL_TRIANGLES);
        if(stlObject.triangles[i].isGood)
            glColor3ub(color.r, color.g, color.b);
        else
            glColor3ub(colorCut.r, colorCut.g, colorCut.b);
        glVertex3f(stlObject.triangles[i].vertex[0].x, stlObject.triangles[i].vertex[0].y, stlObject.triangles[i].vertex[0].z);
        glVertex3f(stlObject.triangles[i].vertex[1].x, stlObject.triangles[i].vertex[1].y, stlObject.triangles[i].vertex[1].z);
        glVertex3f(stlObject.triangles[i].vertex[2].x, stlObject.triangles[i].vertex[2].y, stlObject.triangles[i].vertex[2].z);
        glEnd();
    }*/
    // ---
    for(size_t i = 0; i < stlObject.additional.size(); i++){
        glBegin(GL_TRIANGLES);
        if(stlObject.additional[i].isGood)
            glColor3ub(color.red(), color.green(), color.blue());
        else
            glColor3ub(colorCut.red(), colorCut.green(), colorCut.blue());
        glVertex3f(stlObject.additional[i].vertex[0].x(), stlObject.additional[i].vertex[0].y(), stlObject.additional[i].vertex[0].z());
        glVertex3f(stlObject.additional[i].vertex[1].x(), stlObject.additional[i].vertex[1].y(), stlObject.additional[i].vertex[1].z());
        glVertex3f(stlObject.additional[i].vertex[2].x(), stlObject.additional[i].vertex[2].y(), stlObject.additional[i].vertex[2].z());
        glEnd();
    }
    // ---
    if(basePoint){
        QMap<QString, QVector3D>::const_iterator chlPt;
        for(chlPt = childrenPoints.begin(); chlPt != childrenPoints.end(); chlPt++){
            glLineWidth(2.0f);
            glBegin(GL_LINES);
            glColor3ub(colOrange.red(), colOrange.green(), colOrange.blue());
            glVertex3f(basePoint->x(), basePoint->y(), basePoint->z());
            glVertex3f(chlPt.value().x(), chlPt.value().y(), chlPt.value().z());
            glEnd();
        }
        QMap<QString, QVector3D>::const_iterator inter;
        for (inter = intersections.begin(); inter != intersections.end(); inter++){
            glPointSize(6.0f);
            glBegin(GL_POINTS);
            glVertex3f(inter.value().x(), inter.value().y(), inter.value().z());
            glEnd();
        }
    }
}

void man::AbstractBone::drawBasePoint() const
{
    if(!basePoint) return;

    QColor bp = Qt::darkRed;
    glLineWidth(2.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(bp.red(), bp.green(), bp.blue());
    glVertex3f(basePoint->x() - 1, basePoint->y(), basePoint->z() + 1);
    glVertex3f(basePoint->x() + 1, basePoint->y(), basePoint->z() + 1);
    glVertex3f(basePoint->x(), basePoint->y(), basePoint->z() - 1);
    glEnd();
}

QMap<QString, QVariant> man::AbstractBone::getPropertyList() const
{

}

void man::AbstractBone::serialize()
{
    //std::cout << "Serialize AbsBone: " <<  name.toStdString() << std::endl; // NOTE: delete
}
