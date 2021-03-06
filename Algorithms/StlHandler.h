#ifndef STLHANDLER_H
#define STLHANDLER_H

#include "Auxiliary/ExtraMath.h"
#include "Auxiliary/Additional.h"
#include "Config/Defines.h"
#include "Entities/Primitives.h"

namespace man{

class StlHandler
{
public:
    StlHandler();

    Status parseFromFile(QString &pathToFile, StlObject &object);    

    Status saveToFile(const QString &pathToDir, StlObject &object);

private:
    const std::string keyWSolid          = "solid";
    const std::string keyWFacetNormal    = "facet normal";
    const std::string keyWVertex         = "vertex";

    StlFormat isStlASCII(QString &pathToFile);

    Status parseFromFileASCII(const QString &pathToFile, StlObject &object);
    void obtainFromBlocks(std::string &rawString, const std::string &keyWord, QVector3D &data);

    Status parseFromFileBinary(const QString &pathToFile, StlObject &object);
};

}

#endif // STLHANDLER_H
