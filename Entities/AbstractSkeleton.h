#ifndef ABSTRACTSKELETON_H
#define ABSTRACTSKELETON_H

#include <QString>

#include "Config/Config.h"
#include "AbstractBone.h"
#include "CyberBone.h"
#include "HumanBone.h"
#include "Algorithms/StlHandler.h"

namespace man{

class AbstractSkeleton
{
public:
    AbstractSkeleton();
    virtual ~AbstractSkeleton();

    QString name;    

    QMap<QString, AbstractBone*>bones;

    bool isConstructDone = false;

    float height = 0.0f;

    StlHandler stlReader;

    virtual man::Status loadFromJson(const Config& config, bool isHuman);
    virtual man::Status construct();

    void rotateBonesFull(AbstractBone* startBone, const Point3F &angles);
    void rotateBonesSingle(AbstractBone* startBone, const Point3F &angles);

private:
    void calcHeight();

};

}

#endif // ABSTRACTSKELETON_H
