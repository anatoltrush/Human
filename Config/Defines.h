#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>

#include <QMap>
#include <QDir>
#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QCoreApplication>

namespace man{

enum Status{
    StatusOk                = 0,

    // not found
    StatusFileNotFound      = -1,
    StatusDirNotFound       = -2,

    //bones
    StatusBoneNotFound      = -3,
    StatusBoneNotLoaded     = -4,

    // empty
    StatusDirIsEmpty        = -5,
    StatusFileIsEmpty       = -6,
    StatusPathIsEmpty       = -7,
    StatusJsonListIsEmpty   = -8,
    StatusBonesListIsEmpty  = -9,

    // other
    StatusNotFinished       = -10,
    StatusBadFileFormat     = -11
};

enum Material{
    HumanTissue,
    Plastic,
    Metal
};

enum StlFormat{
    StlASCII        = 1,
    StlBinary       = 2
};

}

#endif // DEFINES_H
