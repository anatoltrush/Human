#ifndef ABSTRACTSKELETON_H
#define ABSTRACTSKELETON_H

#include <QString>

#include "Config/Config.h"
#include "CyberBone.h"
#include "HumanBone.h"
#include "Algorithms/StlHandler.h"

namespace man{

class AbstractSkeleton: public IProperty
{
public:
    AbstractSkeleton();
    virtual ~AbstractSkeleton();

    QString name;    

    QMap<QString, AbstractBone*>bones;

    bool isHuman = true;
    bool isConstructDone = false;

    float height = 0.0f;

    StlHandler stlHandler;

    virtual man::Status loadFromJson(const Config& config);
    virtual man::Status construct();

    AbstractBone* getStartBone();
    void rotateBonesSingle(AbstractBone* startBone, const Angle &angles);

    virtual QMap<QString, QVariant> getPropertyList() const override;

    void resetBonesExist();

    virtual Status serialize(const QString &pathDir);

private:
    void calcHeight();

    void rotateBonesAll(AbstractBone* startBone);
};

}

#endif // ABSTRACTSKELETON_H
