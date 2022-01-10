#include "StlHandler.h"

man::StlHandler::StlHandler()
{

}

man::Status man::StlHandler::parseFromFile(const QString &pathToFile, StlObject &object)
{
    StlFormat isFileASCII = isStlASCII(pathToFile);
    if(isFileASCII == StlASCII){
        Status resASCII = parseFromFileASCII(pathToFile, object);
        return resASCII;
    }
    else if(isFileASCII == StlBinary){
        Status resBinary = parseFromFileBinary(pathToFile, object);
        return resBinary;
    }
    else{
        return StatusFileNotFound;
    }
}

void man::StlHandler::calcAddProps(StlObject &object)
{
    calcSquare(object);
    calcVolume(object);
}

man::Status man::StlHandler::svaeToFile(const QString &pathToFile, man::StlObject &object)
{

}

man::StlFormat man::StlHandler::isStlASCII(const QString &pathToFile)
{
    std::ifstream inputFileData(pathToFile.toStdString().data());
    if(!inputFileData) return StlBadFormat;

    uint16_t startReadSize = 512; // NOTE: stl config
    char chars [startReadSize];
    inputFileData.read(chars, startReadSize);
    std::string strData(chars, inputFileData.gcount());

    return (strData.find(keyWFacetNormal) != std::string::npos) ? StlASCII : StlBinary;
}

man::Status man::StlHandler::parseFromFileASCII(const QString &pathToFile, StlObject &object)
{
    object.clear();
    //-----
    std::ifstream inputFileData(pathToFile.toStdString().data());
    if(!inputFileData) return StatusFileNotFound;

    std::string buffer;
    std::vector<std::string> fileStrings;
    while (!inputFileData.eof()) {
        getline(inputFileData, buffer);
        fileStrings.push_back(buffer);
    }

    if(fileStrings.size() == 0) return StatusFileIsEmpty;

    if(fileStrings[0].find(keyWSolid) != std::string::npos){
        std::string stlName = fileStrings[0];
        object.objectName = QString::fromStdString(stlName.erase(0, keyWSolid.size() + 1));
    }
    else
        return StatusBadFileFormat;
    // -----
    int stringsInBlock = 7; // NOTE: config stringsInBlock
    for(size_t i = 0; i < fileStrings.size(); i++){
        if(fileStrings[i].find(keyWSolid) != std::string::npos){
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
        return StatusBadFileFormat;
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
        obtainFromBlocks(normal, keyWFacetNormal, triangle.normal);

        std::string vertex0 = blocks[i][2];
        obtainFromBlocks(vertex0, keyWVertex, triangle.vertex[0]);

        std::string vertex1 = blocks[i][3];
        obtainFromBlocks(vertex1, keyWVertex, triangle.vertex[1]);

        std::string vertex2 = blocks[i][4];
        obtainFromBlocks(vertex2, keyWVertex, triangle.vertex[2]);

        object.triangles.push_back(triangle);
    }
    return StatusOk;
}

void man::StlHandler::obtainFromBlocks(std::string &rawString, const std::string &keyWord, Point3F &data)
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

man::Status man::StlHandler::parseFromFileBinary(const QString &pathToFile, StlObject &object)
{
    object.clear();
    //-----
    std::ifstream inputFileData(pathToFile.toStdString().data(), std::ios::binary);
    if(!inputFileData) return StatusFileNotFound;

    size_t headerSize = 80;
    char header[headerSize];
    inputFileData.read(header, headerSize);

    uint32_t numTriangles = 0;
    inputFileData.read((char*)&numTriangles, 4);

    for(uint32_t i = 0; i < numTriangles; i++){
        uint8_t triReadSize = 12; // NOTE: stl config
        float triData[triReadSize];
        inputFileData.read((char*)triData, triReadSize * 4);

        Triangle triangle;
        triangle.normal.x = triData[0];
        triangle.normal.y = triData[1];
        triangle.normal.z = triData[2];
        for(size_t indVert = 0; indVert < 3; indVert++){
            triangle.vertex[indVert].x = triData[(indVert + 1) * 3 + 0];
            triangle.vertex[indVert].y = triData[(indVert + 1) * 3 + 1];
            triangle.vertex[indVert].z = triData[(indVert + 1) * 3 + 2];
        }

        uint8_t attBtCntSize = 2;
        char abcData[attBtCntSize];
        inputFileData.read(abcData, attBtCntSize);
        std::memcpy(&triangle.attrByteCount, &abcData, sizeof(triangle.attrByteCount));

        object.triangles.push_back(triangle);
    }

    return StatusOk;
}

void man::StlHandler::calcSquare(StlObject &object)
{
    object.square = 0.0f;
    for(const auto &tri : object.triangles){
        float ab = distance(tri.vertex[0], tri.vertex[1]);
        float bc = distance(tri.vertex[1], tri.vertex[2]);
        float ca = distance(tri.vertex[2], tri.vertex[0]);

        float per = (ab + bc + ca) / 2;

        float sqrTri = sqrt(per * (per - ab) * (per - bc) * (per - ca));
        object.square += sqrTri;
    }
}

void man::StlHandler::calcVolume(StlObject &object)
{

}

float man::StlHandler::distance(const Point3F &ptA, const Point3F &ptB)
{
    return sqrt((ptB.x - ptA.x) * (ptB.x - ptA.x)
                + (ptB.y - ptA.y) * (ptB.y - ptA.y)
                + (ptB.z - ptA.z) * (ptB.z - ptA.z));
}
