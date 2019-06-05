#pragma once

#include "iencoder.hpp"



class SimpleEncoder :virtual public IEncoder
{
public:
    SimpleEncoder();

    // IEncoder interface
public:
    void Encode(std::ifstream &photo, std::ifstream &data, std::ofstream &output);
    void Decode(std::ifstream &photo, std::ofstream &output);
    void Clear(std::ifstream &photo, std::ofstream &output);
};
