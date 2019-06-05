#include <memory>
#include "communicator.hpp"
#include "../encoders/simpleencoder.hpp"
#include "../info.hpp"



void Communicator::Action(Arguments *args)
{
    InitializeEncoder(EncoderTypeEnum::simple);  //td
    if(args->carrierPath.compare(args->outputPath) == 0)
        throw std::invalid_argument(std::string("Carrier and output could not be the same file"));
    switch(args->mode)
    {
        case Arguments::Mode::write:
            Encode(args->carrierPath, args->dataPath, args->outputPath);
            break;
        case Arguments::Mode::read:
            Decode(args->carrierPath, args->outputPath);
            break;
        case Arguments::Mode::clear:
            Clear(args->carrierPath, args->outputPath);
            break;
        case Arguments::Mode::version:
            std::cout << Info::programName + " " + Info::detailedVersion << std::endl;
            break;
        case Arguments::Mode::help:
            std::cout << Info::help << std::endl;
            break;
        default:
            throw std::invalid_argument(std::string("unhandled mode in communicator"));
    }
}


int Communicator::InitializeEncoder(Communicator::EncoderTypeEnum encoderType)
{
    switch (encoderType)
    {
        case EncoderTypeEnum::simple:
            _encoder = new SimpleEncoder();
            break;
        default:
            throw std::invalid_argument(std::string("Not a valid encoder type"));
    }
}


int Communicator::Encode(std::string carrierPath, std::string dataPath, std::string outputPath)
{
    std::ifstream photo;
    photo.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    std::ifstream data;
    data.open(dataPath,std::ios_base::in | std::ios_base::binary);
    std::ofstream output;
    output.open(outputPath,std::ios_base::out | std::ios_base::binary);
    if (!photo.is_open())
    {
        throw std::invalid_argument( carrierPath + std::string(" couldn't be opened"));
    }
    if (!data.is_open())
    {
        photo.close();
        throw std::invalid_argument( dataPath + std::string(" couldn't be opened"));
    }
    if (!output.is_open())
    {
        photo.close();
        data.close();
        throw std::invalid_argument( outputPath + std::string(" couldn't be opened"));
    }
    try
    {
        unsigned char temp;
        unsigned char temp2;
        photo.read((char*)(&temp), 1);
        photo.read((char*)(&temp2), 1);
        if(temp != 0xFF || temp2 != 0xD8)
            throw std::invalid_argument( carrierPath + std::string(" file is not JPG, or is corrupted"));
        photo.seekg(0, std::ios::beg);
    }
    catch (...)
    {
        throw std::invalid_argument( carrierPath + std::string(" file is not JPG, or is corrupted"));
    }
    _encoder->Encode(photo, data, output);

    photo.close();
    data.close();
    output.close();
    return 0;
}


int Communicator::Decode(std::string carrierPath, std::string outputPath)
{
    std::ifstream photo;
    photo.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    std::ofstream output;
    output.open(outputPath,std::ios_base::out | std::ios_base::binary);
    if (!photo.is_open())
    {
        throw std::invalid_argument( carrierPath + std::string(" couldn't be opened"));
    }
    if (!output.is_open())
    {
        photo.close();
        throw std::invalid_argument( outputPath + std::string(" couldn't be opened"));
    }

    _encoder->Decode(photo, output);

    photo.close();
    output.close();
    return 0;
}


int Communicator::Clear(std::string carrierPath, std::string outputPath)
{
    std::ifstream photo;
    photo.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    std::ofstream output;
    output.open(outputPath,std::ios_base::out | std::ios_base::binary);
    if (!photo.is_open())
    {
        throw std::invalid_argument( carrierPath + std::string(" couldn't be opened"));
    }
    if (!output.is_open())
    {
        photo.close();
        throw std::invalid_argument( outputPath + std::string(" couldn't be opened"));
    }

    _encoder->Clear(photo, output);

    photo.close();
    output.close();
    return 0;
}
