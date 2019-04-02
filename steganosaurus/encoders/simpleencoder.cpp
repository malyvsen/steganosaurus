#include <iostream>
#include <fstream>
#include "simpleencoder.hpp"



SimpleEncoder::SimpleEncoder()
{

}

int SimpleEncoder::Encode(std::ifstream &photo, std::ifstream &data, std::ofstream &output)
{
    output << photo.rdbuf();
    output << data.rdbuf();
    int dataSize = data.tellg();
    std::cout << dataSize << std::endl;
    std::cout << (char*)&dataSize << std::endl;
    output << ((char*)&dataSize)[3];
    output << ((char*)&dataSize)[2];
    output << ((char*)&dataSize)[1];
    output << ((char*)&dataSize)[0];
}

int SimpleEncoder::Decode(std::ifstream &photo, std::ofstream &output)
{
    photo.seekg (0, std::ios::end);
    int pfotoSize = photo.tellg();
    char *memblock = new char [pfotoSize];
    photo.seekg (0, std::ios::beg);
    photo.read (memblock, pfotoSize);
    char dataSizeBuf[4];
    for(int i = 0; i< 4; i++)
        dataSizeBuf[i] = memblock[pfotoSize - 1 - i];
    int dataSize = *(int*)dataSizeBuf;
    std::cout << dataSize << std::endl;
    for(int i = 0; i < dataSize; i++)
        output << memblock[pfotoSize - 4 - dataSize + i];
    delete[] memblock;
}

int SimpleEncoder::Clear(std::ifstream &photo, std::ofstream &output)
{
    photo.seekg (0, std::ios::end);
    int pfotoSize = photo.tellg();
    char *memblock = new char [pfotoSize];
    photo.seekg (0, std::ios::beg);
    photo.read (memblock, pfotoSize);
    char dataSizeBuf[4];
    for(int i = 0; i< 4; i++)
        dataSizeBuf[i] = memblock[pfotoSize - 1 - i];
    int dataSize = *(int*)dataSizeBuf;
    for(int i = 0; i < pfotoSize - dataSize - 4; i++)
        output << memblock[i];
    delete[] memblock;
}
