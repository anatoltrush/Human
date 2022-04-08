#include "AbstractBone.h"

man::AbstractBone::AbstractBone(){}

man::AbstractBone::~AbstractBone(){}

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
    rotationStart.setX(rotate["x"].toDouble());
    rotationStart.setY(rotate["y"].toDouble());
    rotationStart.setZ(rotate["z"].toDouble());
}

void man::AbstractBone::rotateBone(const QVector3D &centerPoint, const Angle &angles)
{
    // --- children points ---
    for(auto &chlPt : childrenPoints)
        chlPt = rotatePoint3F(chlPt, angles.degToRad(), centerPoint);

    // --- stl ---
    for(auto &tr : stlObject.triangles)
        for(auto &vr : tr.vertex)
            vr = rotatePoint3F(vr, angles.degToRad(), centerPoint);

    // --- base point ---
    basePoint = rotatePoint3F(basePoint, angles.degToRad(), centerPoint);

    // --- anchorPoint ---
    anchorDirect = rotatePoint3F(anchorDirect, angles.degToRad(), centerPoint);
    anchorDown = rotatePoint3F(anchorDown, angles.degToRad(), centerPoint);

    // --- write angle ---
    std::vector<QVector3D> tempVec;
    for(const auto &chlPt : qAsConst(childrenPoints))
        tempVec.push_back(chlPt);
    QVector3D tempPoint = getCenter(tempVec);
    rotationCurrent = angle3Pts0_180Reverse(tempPoint, basePoint);
    //rotationCurrent = angle3Pts0_180Reverse(anchorDown, basePoint);
}

void man::AbstractBone::applyOffsets(const QVector3D &offset)
{
    anchorDirect = anchorDown = basePoint;
    anchorDirect += QVector3D(anchorOffset.x(), anchorOffset.y(), anchorOffset.z());
    anchorDown += QVector3D(0.0f, 0.0f, anchorOffset.z());
    // -----
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

void man::AbstractBone::drawObjectGL()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // --- STL main ---
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
    // --- STL add ---
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
    // --- connections ---
    for(auto chlPt = childrenPoints.begin(); chlPt != childrenPoints.end(); chlPt++){
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        // just bones
        glColor3ub(colorHull.red(), colorHull.green(), colorHull.blue());
        glVertex3f(basePoint.x(), basePoint.y(), basePoint.z());
        glVertex3f(chlPt.value().x(), chlPt.value().y(), chlPt.value().z());
        // tendon
        /*glColor3ub(colorCut.red(), colorCut.green(), colorCut.blue());
        glVertex3f(basePoint.x(), basePoint.y(), basePoint.z());
        glVertex3f(basePoint.x() + parentOffset.x(), basePoint.y() + parentOffset.y(), basePoint.z() + parentOffset.z());
        // bone
        glColor3ub(colorHull.red(), colorHull.green(), colorHull.blue());
        glVertex3f(basePoint.x() + parentOffset.x(), basePoint.y() + parentOffset.y(), basePoint.z() + parentOffset.z());
        glVertex3f(chlPt.value().x(), chlPt.value().y(), chlPt.value().z());*/
        glEnd();
    } // --- intersections ---
    for (auto inter = intersections.begin(); inter != intersections.end(); inter++){
        glPointSize(6.0f);
        glBegin(GL_POINTS);
        glVertex3f(inter.value().x(), inter.value().y(), inter.value().z());
        glEnd();
    }
}

void man::AbstractBone::drawBasePoint() const
{
    QColor bp = Qt::darkRed;
    glLineWidth(2.0f);
    glBegin(GL_TRIANGLES);
    glColor3ub(bp.red(), bp.green(), bp.blue());
    glVertex3f(basePoint.x() - 1, basePoint.y(), basePoint.z() + 1);
    glVertex3f(basePoint.x() + 1, basePoint.y(), basePoint.z() + 1);
    glVertex3f(basePoint.x(), basePoint.y(), basePoint.z() - 1);
    glEnd();
}

void man::AbstractBone::drawExt() const
{
    QColor bp = Qt::darkCyan;
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3ub(bp.red(), bp.green(), bp.blue());
    glVertex3f(anchorDirect.x(), anchorDirect.y(), anchorDirect.z());
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(bp.red(), bp.green(), bp.blue());
    glVertex3f(anchorDown.x(), anchorDown.y(), anchorDown.z());
    glEnd();
}

QMap<QString, QVariant> man::AbstractBone::getPropertyList() const
{
    QMap<QString, QVariant> props;
    props["name"] = this->name;
    props["material"] = this->material;
    props["squareFull"] = QString::fromStdString(floatShort(this->stlObject.squareFull, 1));
    props["squareCut"] = QString::fromStdString(floatShort(this->stlObject.squareCut, 1));
    props["volumeFull"] = QString::fromStdString(floatShort(this->stlObject.volumeFull, 1));
    props["volumeCut"] = QString::fromStdString(floatShort(this->stlObject.volumeCut, 1));
    props["triangles"] = (int)this->stlObject.triangles.size();
    return props;
}

void man::AbstractBone::serialize(){}
