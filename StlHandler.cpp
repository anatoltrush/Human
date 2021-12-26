#include "StlHandler.h"

man::StlHandler::StlHandler()
{

}

int man::StlHandler::parseFromFile(const QString &pathToFile, StlObject &object)
{
    object.clear();
    //-----
    std::ifstream inputFileData(pathToFile.toStdString().data());
    if(!inputFileData) return statusFileNotFound;

    std::string buffer;
    std::vector<std::string> fileStrings;
    while (!inputFileData.eof()) {
        getline(inputFileData, buffer);
        fileStrings.push_back(buffer);
    }

    if(fileStrings.size() == 0) return statusFileIsEmpty;

    if(fileStrings[0].find(keySolid + " ") < fileStrings[0].size())
        object.objectName = QString::fromStdString(fileStrings[0].erase(0, keySolid.size() + 1));
    else
        return statusBadFileFormat;
    // -----
    int stringsInBlock = 7; // NOTE: config stringsInBlock
    fileStrings.erase(fileStrings.begin());
    fileStrings.erase(fileStrings.end());
    if(fileStrings.size() % stringsInBlock != 0) return statusBadFileFormat;
    // -----
    std::vector<std::vector<std::string>> blocks;
    int numBlocks = fileStrings.size() / stringsInBlock;
    blocks.resize(numBlocks);

    // Fill blocks
    for(int i = 0; i < numBlocks; i++)
        for(int j = 0; j < stringsInBlock; j++)
            blocks[i].push_back(fileStrings[i * stringsInBlock + j]);

    return statusOk;
}
