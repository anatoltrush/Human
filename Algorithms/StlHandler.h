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

private:
    const std::string keyWSolid          = "solid";
    const std::string keyWFacetNormal    = "facet normal";
    const std::string keyWVertex         = "vertex";

    int isStlASCII(const QString &pathToFile);

    int parseFromFileASCII(const QString &pathToFile, StlObject &object);
    void obtainFromBlocks(std::string &rawString, const std::string &keyWord, Point3F &data);

    int parseFromFileBinary(const QString &pathToFile, StlObject &object);
};

}

#endif // STLHANDLER_H
