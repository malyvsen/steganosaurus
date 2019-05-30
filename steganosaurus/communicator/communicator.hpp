#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include "../encoders/iencoder.hpp"
#include "../interface/arguments.hpp"



class Communicator
{
    public:
        static Communicator& getInstance()
        {
            static Communicator instance;
            return instance;
        }
        Communicator(Communicator const&)   = delete;
        void operator=(Communicator const&)  = delete;

        int Action(Arguments *args);
        ~Communicator()
        {
            if(_encoder != nullptr)
                delete _encoder;
        }
private:
    Communicator() {}
    enum class EncoderTypeEnum{unknown = -1 , simple = 0};

    int InicializeEncoder(EncoderTypeEnum encoderType);
    int Encode(std::string carrierPath, std::string dataPath, std::string outputPath);
    int Decode(std::string carrierPath, std::string outputPath);
    int Clear(std::string carrierPath, std::string outputPath);


    //std::unique_ptr<IEncoder> _encoder;

    IEncoder *_encoder = nullptr;
};
