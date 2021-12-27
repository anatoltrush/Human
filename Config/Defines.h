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
    statusOk                = 0,

    statusFileNotFound      = -1,
    statusDirNotFound       = -2,

    statusBoneNotFound      = -3,

    statusDirIsEmpty        = -4,
    statusFileIsEmpty       = -5,
    statusPathIsEmpty       = -6,
    statusJsonListIsEmpty   = -7,
    statusBonesListIsEmpty  = -8,

    statusNotFinished       = -9,
    statusBadFileFormat     = 10
};

enum Material{
    HumanTissue,
    Plastic,
    Metal
};

}

#endif // DEFINES_H
