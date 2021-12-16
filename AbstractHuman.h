#ifndef ABSTRACTHUMAN_H
#define ABSTRACTHUMAN_H

#include <string_view>

#include <QDateTime>

namespace man{

class AbstractHuman
{
public:
    AbstractHuman();

    std::string_view firstName; // name
    std::string_view lastName; // family
    QDateTime birth;
};

}

#endif // ABSTRACTHUMAN_H
