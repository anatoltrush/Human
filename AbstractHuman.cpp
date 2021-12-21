#include "AbstractHuman.h"

man::AbstractHuman::AbstractHuman()
{

}

man::AbstractHuman::~AbstractHuman()
{
    delete skeleton;
}

int man::AbstractHuman::loadSkeleton(const Config &config)
{
    QString pathToEntityRel = config.pathsToSkeletons[skeleton->name];
    QString pathToEntityAbs = config.pathApplication + "/" + pathToEntityRel;
    int loadSkeletonResult = skeleton->loadFromJson(pathToEntityAbs);
    return loadSkeletonResult;
}
