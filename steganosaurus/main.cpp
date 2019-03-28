#include <iostream>
#include <communicator/communicator.h>
#include <interface/arguments.hpp>
using namespace std;

int main(int argc,char** argv)
{
    Arguments *arg = new Arguments(argc, argv);
    Communicator::getInstance().Action(arg);
    delete arg;
    return 0;
}

