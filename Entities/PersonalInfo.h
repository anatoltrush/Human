#ifndef PERSONALINFO_H
#define PERSONALINFO_H

#include <QDateTime>

namespace man{

class PersonalInfo
{
public:
    PersonalInfo();

    QString firstName; // name

    QString lastName; // family

    QString address;

    QDateTime birthDay;

};

}

#endif // PERSONALINFO_H
