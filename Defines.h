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

// --- ERRORS ---
enum Status{
    statusOk                = 0,

    statusFileNotFound      = -1,
    statusDirNotFound       = -2,

    statusBoneNotFound      = -3,

    statusDirIsEmpty        = -4,
    statusPathIsEmpty       = -5,
    statusJsonListIsEmpty   = -6,
    statusBonesListIsEmpty  = -7,

    statusNotFinished       = -8
};

#endif // DEFINES_H
