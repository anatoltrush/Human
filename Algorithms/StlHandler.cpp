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

    if(fileStrings[0].find(keyWSolid + " ") < fileStrings[0].size()){
        std::string stlName = fileStrings[0];
        object.objectName = QString::fromStdString(stlName.erase(0, keyWSolid.size() + 1));
    }
    else
        return statusBadFileFormat;
    // -----
    int stringsInBlock = 7; // NOTE: config stringsInBlock
    for(size_t i = 0; i < fileStrings.size(); i++){
        if(fileStrings[i].find(keyWSolid + " ") < fileStrings[0].size()){
            fileStrings.erase(fileStrings.begin() + i);
            i--;
            continue;
        }
        if(fileStrings[i].size() == 0){
            fileStrings.erase(fileStrings.begin() + i);
            i--;
            continue;
        }
    }
    if(fileStrings.size() % stringsInBlock != 0)
        return statusBadFileFormat;
    // -----
    std::vector<std::vector<std::string>> blocks;
    int numBlocks = fileStrings.size() / stringsInBlock;
    blocks.resize(numBlocks);

    // Fill blocks
    for(int i = 0; i < numBlocks; i++)
        for(int j = 0; j < stringsInBlock; j++)
            blocks[i].push_back(fileStrings[i * stringsInBlock + j]);

    // ----- obtain data from blocks -----
    for(size_t i = 0; i < blocks.size(); i++){
        Triangle triangle;

        std::string normal = blocks[i][0];
        obtainData(normal, keyWFacetNormal, triangle.normal);

        std::string vertex0 = blocks[i][2];
        obtainData(vertex0, keyWVertex, triangle.vertex[0]);

        std::string vertex1 = blocks[i][3];
        obtainData(vertex1, keyWVertex, triangle.vertex[1]);

        std::string vertex2 = blocks[i][4];
        obtainData(vertex2, keyWVertex, triangle.vertex[2]);

        object.triangles.push_back(triangle);
    }
    return statusOk;
}

void man::StlHandler::obtainData(std::string &rawString, const std::string &keyWord, Point3F &data)
{
    // from front
    for(size_t i = 0; i < rawString.size(); i++){
        if(rawString[i] == ' '){
            rawString.erase(i, 1);
            i--;
        }
        else break;
    }
    //from back
    for(size_t i = rawString.size() - 1; i >= 0; i--){
        if(rawString[i] == ' ')
            rawString.erase(i, 1);
        else break;
    }
    // keyword
    rawString.erase(0, keyWord.size() + 1);
    // data
    QString strData = QString::fromStdString(rawString);
    QStringList strFloats = strData.split(' ');
    data.x = strFloats[0].toFloat();
    data.y = strFloats[1].toFloat();
    data.z = strFloats[2].toFloat();
}
