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

    StatusDirIsEmpty        = -4,
    StatusFileIsEmpty       = -5,
    StatusPathIsEmpty       = -6,
    StatusJsonListIsEmpty   = -7,
    StatusBonesListIsEmpty  = -8,

    StatusNotFinished       = -9,
    StatusBadFileFormat     = 10
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
