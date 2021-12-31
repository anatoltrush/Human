#ifndef STLHANDLER_H
#define STLHANDLER_H

#include <iostream>
#include <fstream>

#include "Config/Defines.h"
#include "Entities/Primitives.h"

namespace man{

class StlHandler
{
public:
    StlHandler();

    int parseFromFile(const QString &pathToFile, StlObject &object);
    void calcAddProps(StlObject &object);

private:
    const std::string keyWSolid          = "solid";
    const std::string keyWFacetNormal    = "facet normal";
    const std::string keyWVertex         = "vertex";

    int isStlASCII(const QString &pathToFile);

    int parseFromFileASCII(const QString &pathToFile, StlObject &object);
    void obtainFromBlocks(std::string &rawString, const std::string &keyWord, Point3F &data);

    int parseFromFileBinary(const QString &pathToFile, StlObject &object);

    void calcSquare(StlObject &object);
    void calcVolume(StlObject &object);

    float distance(const Point3F &ptA, const Point3F &ptB);
};

}

#endif // STLHANDLER_H
