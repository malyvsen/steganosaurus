#pragma once

#include <iostream>

#include "iencoder.hpp"



class SimpleEncoder :virtual public IEncoder
{
public:
    SimpleEncoder();

    // IEncoder interface
public:
    void Encode(std::istream &photo, std::istream &data, std::ostream &output);
    void Decode(std::istream &photo, std::ostream &output);
    void Clear(std::istream &photo, std::ostream &output);
};
