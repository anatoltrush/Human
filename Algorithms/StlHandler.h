#ifndef STLHANDLER_H
#define STLHANDLER_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "Config/Defines.h"
#include "Entities/Primitives.h"

namespace man{

class StlHandler
{
public:
    StlHandler();

    Status parseFromFile(const QString &pathToFile, StlObject &object);
    void calcAddProps(StlObject &object);

    Status svaeToFile(const QString &pathToFile, StlObject &object);

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

    float distance(const Point3F &ptA, const Point3F &ptB);
};

}

#endif // STLHANDLER_H
