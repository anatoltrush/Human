#include "Additional.h"

std::string man::floatToScience(float value)
{
    std::stringstream stream;
    stream << std::fixed << std::scientific << value;
    return stream.str();
}

std::string man::floatShort(float value, int after)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(after) << value;
    return stream.str();
}
