#ifndef SIMPLEENCODER_H
#define SIMPLEENCODER_H

#include <encoders/iencoder.h>
class SimpleEncoder :virtual public IEncoder
{
public:
    SimpleEncoder();

    // IEncoder interface
public:
    int Encode(std::ifstream &photo, std::ifstream &data, std::ofstream &output);
    int Decode( std::ifstream &photo, std::ofstream &output);
};

#endif // SIMPLEENCODER_H
