#pragma once

#include <fstream>



class IEncoder
{
public:
    IEncoder();
    void virtual Encode(std::ifstream &photo, std::ifstream &data, std::ofstream &output) = 0;
    void virtual Decode(std::ifstream &photo, std::ofstream &output) = 0;
    void virtual Clear(std::ifstream &photo, std::ofstream &output) = 0;
};
