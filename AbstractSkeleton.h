#ifndef ABSTRACTSKELETON_H
#define ABSTRACTSKELETON_H

#include <map>

namespace man{

class AbstractSkeleton
{
public:
    AbstractSkeleton();

    virtual void loadFromJson() = 0;
};

}

#endif // ABSTRACTSKELETON_H
