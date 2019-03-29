#pragma once

#include "iencoder.hpp"



class SimpleEncoder :virtual public IEncoder
{
public:
    SimpleEncoder();

    // IEncoder interface
public:
    int Encode(std::ifstream &photo, std::ifstream &data, std::ofstream &output);
    int Decode( std::ifstream &photo, std::ofstream &output);
};
