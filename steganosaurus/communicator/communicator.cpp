#include <memory>
#include "communicator.hpp"
#include "../encoders/simpleencoder.hpp"
#include "../info.hpp"



void Communicator::Action(Arguments *args)
{
    InitializeEncoder(EncoderTypeEnum::simple);  //td
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


void Communicator::InitializeEncoder(Communicator::EncoderTypeEnum encoderType)
{
    switch (encoderType)
    {
        case EncoderTypeEnum::simple:
            _encoder = new SimpleEncoder();
            break;
        default:
            throw std::invalid_argument(std::string("invalid encoder type"));
    }
}


void Communicator::Encode(std::string carrierPath, std::string dataPath, std::string outputPath)
{
    std::ifstream photoFile; std::stringstream photoStream;
    photoFile.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    if (!photoFile.is_open()) throw std::invalid_argument(carrierPath + std::string(" couldn't be opened"));
    photoStream << photoFile.rdbuf();
    photoFile.close();

    std::ifstream dataFile; std::stringstream dataStream;
    dataFile.open(dataPath,std::ios_base::in | std::ios_base::binary);
    if (!dataFile.is_open()) throw std::invalid_argument(dataPath + std::string(" couldn't be opened"));
    dataStream << dataFile.rdbuf();
    dataFile.close();

    std::ofstream outputFile;
    outputFile.open(outputPath, std::ios_base::out | std::ios_base::binary);
    if (!outputFile.is_open()) throw std::invalid_argument(outputPath + std::string(" couldn't be opened"));

    try
    {
        unsigned char temp;
        unsigned char temp2;
        photoStream.read((char*)(&temp), 1);
        photoStream.read((char*)(&temp2), 1);
        if(temp != 0xFF || temp2 != 0xD8)
            throw std::invalid_argument(carrierPath + std::string(" is not JPG, or is corrupted"));
        photoStream.seekg(0, std::ios::beg);
    }
    catch (...)
    {
        throw std::invalid_argument(carrierPath + std::string(" is not JPG, or is corrupted"));
    }
    _encoder->Encode(photoStream, dataStream, outputFile);
}


void Communicator::Decode(std::string carrierPath, std::string outputPath)
{
    std::ifstream photoFile; std::stringstream photoStream;
    photoFile.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    if (!photoFile.is_open()) throw std::invalid_argument(carrierPath + std::string(" couldn't be opened"));
    photoStream << photoFile.rdbuf();
    photoFile.close();

    std::ofstream outputFile;
    outputFile.open(outputPath, std::ios_base::out | std::ios_base::binary);
    if (!outputFile.is_open()) throw std::invalid_argument(outputPath + std::string(" couldn't be opened"));

    _encoder->Decode(photoStream, outputFile);

    outputFile.close();
}


void Communicator::Clear(std::string carrierPath, std::string outputPath)
{
    std::ifstream photoFile; std::stringstream photoStream;
    photoFile.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    if (!photoFile.is_open()) throw std::invalid_argument(carrierPath + std::string(" couldn't be opened"));
    photoStream << photoFile.rdbuf();
    photoFile.close();

    std::ofstream outputFile;
    outputFile.open(outputPath, std::ios_base::out | std::ios_base::binary);
    if (!outputFile.is_open()) throw std::invalid_argument(outputPath + std::string(" couldn't be opened"));

    _encoder->Clear(photoStream, outputFile);

    outputFile.close();
}
