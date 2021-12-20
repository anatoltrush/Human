#ifndef DEFINES_H
#define DEFINES_H

#include <vector>
#include <iostream>

#include <QString>

// --- ERRORS ---
enum Status{
    statusOk = 0,
    statusFileNotFound = -1,
    statusFolderIsEmpty = -2
};

#endif // DEFINES_H
