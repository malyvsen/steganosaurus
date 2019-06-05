#include "simpleencoder.hpp"



SimpleEncoder::SimpleEncoder()
{

}

void SimpleEncoder::Encode(std::istream& photo, std::istream& data, std::ostream& output)
{
    output << photo.rdbuf();
    output << data.rdbuf();
    int dataSize = data.tellg();
    output << ((char*)&dataSize)[3];
    output << ((char*)&dataSize)[2];
    output << ((char*)&dataSize)[1];
    output << ((char*)&dataSize)[0];
}

void SimpleEncoder::Decode(std::istream& photo, std::ostream& output)
{
    photo.seekg (0, std::ios::end);
    int photoSize = photo.tellg();
    char *memblock = new char [photoSize];
    photo.seekg (0, std::ios::beg);
    photo.read (memblock, photoSize);
    char dataSizeBuf[4];
    for(int i = 0; i< 4; i++)
        dataSizeBuf[i] = memblock[photoSize - 1 - i];
    int dataSize = *(int*)dataSizeBuf;
    if(dataSize <= 0 ||  dataSize >= (photoSize - 10))
        throw std::invalid_argument("no data encoded");

    for(int i = 0; i < dataSize; i++)
        output << memblock[photoSize - 4 - dataSize + i];
    delete[] memblock;
}

void SimpleEncoder::Clear(std::istream& photo, std::ostream& output)
{
    photo.seekg (0, std::ios::end);
    int photoSize = photo.tellg();
    char *memblock = new char [photoSize];
    photo.seekg (0, std::ios::beg);
    photo.read (memblock, photoSize);
    char dataSizeBuf[4];
    for(int i = 0; i< 4; i++)
        dataSizeBuf[i] = memblock[photoSize - 1 - i];
    int dataSize = *(int*)dataSizeBuf;
    if(dataSize <= 0 ||  dataSize >= (photoSize - 10))
        throw std::invalid_argument("no data encoded");

    for(int i = 0; i < photoSize - dataSize - 4; i++)
        output << memblock[i];
    delete[] memblock;
}
