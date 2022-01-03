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
#include <QCoreApplication>

namespace man{

// --- ERRORS ---
enum Status{
    StatusOk                = 0,

    StatusFileNotFound      = -1,
    StatusDirNotFound       = -2,

    StatusBoneNotFound      = -3,
    StatusBoneNotLoaded     = -4,

    StatusDirIsEmpty        = -5,
    StatusFileIsEmpty       = -6,
    StatusPathIsEmpty       = -7,
    StatusJsonListIsEmpty   = -8,
    StatusBonesListIsEmpty  = -9,

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
