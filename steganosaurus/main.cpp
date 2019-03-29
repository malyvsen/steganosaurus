#include "_include.hpp"



int main(int argc,char** argv)
{
   auto arguments = Arguments().Parse(argc, argv);
   Communicator::getInstance().Action(&arguments);
   return 0;
}
