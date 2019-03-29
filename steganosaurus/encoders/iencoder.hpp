#pragma once

#include <fstream>



class IEncoder
{
public:
    IEncoder();
    int virtual Encode(std::ifstream &photo, std::ifstream &data, std::ofstream &output) = 0;
    int virtual Decode( std::ifstream &photo, std::ofstream &output) = 0;
};
