#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

namespace man{
    std::string floatToScience(float value);
    std::string floatShort(float value, int after);
}

#endif // ADDITIONAL_H
