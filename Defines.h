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
    statusOk            = 0,
    statusFileNotFound  = -1,
    statusDirNotFound   = -2,
    statusDirIsEmpty    = -3,
    statusPathIsEmpty   = -4,
    statusListIsEmpty   = -5
};

#endif // DEFINES_H
