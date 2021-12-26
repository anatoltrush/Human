#ifndef STLHANDLER_H
#define STLHANDLER_H

#include <iostream>
#include <fstream>

#include "Defines.h"
#include "Primitives.h"

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

    void obtainData(std::string &rawString, const std::string &keyWord, Point3F &data);
};

}

#endif // STLHANDLER_H
