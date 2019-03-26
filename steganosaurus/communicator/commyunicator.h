#ifndef COMMYUNICATOR_H
#define COMMYUNICATOR_H

#include <encoders/iencoder.h>
#include "interface/arguments.hpp"
#include <fstream>
#include <memory>
#include <string>

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


    //std::unique_ptr<IEncoder> _encoder;

    IEncoder *_encoder = nullptr;
};

#endif // COMMYUNICATOR_H
