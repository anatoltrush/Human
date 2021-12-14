#ifndef ABSTRACTHUMAN_H
#define ABSTRACTHUMAN_H

#include <string>

namespace man{

class AbstractHuman
{
public:
    AbstractHuman();

    std::string firstName; // name
    std::string lastName; // family
    uint16_t yearBirth = 0;
};

}

#endif // ABSTRACTHUMAN_H
