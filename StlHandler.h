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
    const std::string keySolid = "solid";
};

}

#endif // STLHANDLER_H
