#pragma once

#include <iostream>



class IEncoder
{
public:
    IEncoder();
    void virtual Encode(std::istream &photo, std::istream &data, std::ostream &output) = 0;
    void virtual Decode(std::istream &photo, std::ostream &output) = 0;
    void virtual Clear(std::istream &photo, std::ostream &output) = 0;
};
