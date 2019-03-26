#include "simpleencoder.h"
#include <iostream>
SimpleEncoder::SimpleEncoder()
{

}

int SimpleEncoder::Encode(std::ifstream &photo, std::ifstream &data, std::ofstream &output)
{
    std::cout << "encoded" << std::endl;
}

int SimpleEncoder::Decode(std::ifstream &photo, std::ofstream &output)
{
    std::cout << "Decoded" << std::endl;
}

