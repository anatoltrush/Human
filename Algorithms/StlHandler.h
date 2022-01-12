#ifndef STLHANDLER_H
#define STLHANDLER_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "Algorithms/ExtraMath.h"
#include "Config/Defines.h"
#include "Entities/Primitives.h"

namespace man{

class StlHandler
{
public:
    StlHandler();

    Status parseFromFile(const QString &pathToFile, StlObject &object);
    void calcAddProperties(StlObject &object);

    Status saveToFile(const QString &pathToDir, StlObject &object);

private:
    const std::string keyWSolid          = "solid";
    const std::string keyWFacetNormal    = "facet normal";
    const std::string keyWVertex         = "vertex";

    StlFormat isStlASCII(const QString &pathToFile);

    Status parseFromFileASCII(const QString &pathToFile, StlObject &object);
    void obtainFromBlocks(std::string &rawString, const std::string &keyWord, Point3F &data);

    Status parseFromFileBinary(const QString &pathToFile, StlObject &object);

    void calcSquare(StlObject &object);
    void calcVolume(StlObject &object);
    std::string flToSc(float value);
};

}

#endif // STLHANDLER_H
