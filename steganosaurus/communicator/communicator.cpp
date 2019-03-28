#include "communicator.h"
#include <encoders/simpleencoder.h>
#include <memory>
int Communicator::Action(Arguments *args)
{
    InicializeEncoder(EncoderTypeEnum::simple);  //td

    switch(args->mode)
    {
        case Arguments::Mode::hide:
            return Encode(args->carrierPath, args->dataPath, args->outputPath);
            break;
        case Arguments::Mode::unhide:
            return Decode(args->carrierPath, args->outputPath);
            break;
        default:
            return -1;
    }
}

int Communicator::InicializeEncoder(Communicator::EncoderTypeEnum encoderType)
{
    switch (encoderType)
    {
        case EncoderTypeEnum::simple:
            _encoder = new SimpleEncoder();
            break;
        default:
            return -100;
        break;
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
        return -2;
    }
    if (!data.is_open())
    {
        return -3;
    }
    if (!output.is_open())
    {
        return -4;
    }

    _encoder->Encode(photo, data, output);

    photo.close();
    data.close();
    output.close();

}

int Communicator::Decode(std::string carrierPath, std::string outputPath)
{
    std::ifstream photo;
    photo.open(carrierPath,std::ios_base::in | std::ios_base::binary);
    std::ofstream output;
    output.open(outputPath,std::ios_base::out | std::ios_base::binary);
    if (!photo.is_open())
    if (!photo.is_open())
    {
        return -2;
    }
    if (!output.is_open())
    {
        return -4;
    }

    _encoder->Decode(photo, output);

    photo.close();
    output.close();
}