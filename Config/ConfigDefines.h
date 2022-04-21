#ifndef CONFIGDEFINES_H
#define CONFIGDEFINES_H

#include "Defines.h"

namespace man{

const QString fileSettings          = "Settings.json";
const QString fileEntities          = "EntitiesConfig.json";

const QString jsonFieldLoadFrom     = "loadFrom";
const QString jsonFieldEntities     = "entities";

const QString jsonFieldSkeletons    = "skeletons";
const QString jsonFieldName         = "name";
const QString jsonFieldPath         = "path";
const QString jsonFieldPath3D       = "model3D";
const QString jsonFieldParent       = "parent";
const QString jsonFieldAlias        = "alias";
const QString jsonFieldChildren     = "children";
const QString jsonFieldRotate       = "rotation";
const QString jsonFolderPathModels  = "modelsFolder";

// --- ENTITIES ---
const QString cyberSkeleton         = "CyberSkeleton";
const QString humanSkeleton         = "HumanSkeleton";

const QString notAvlbl              = "na";

}

#endif // CONFIGDEFINES_H
