#include "_include.hpp"



int main(int argc,char** argv)
{
   Arguments *arg = new Arguments(argc, argv);
   Communicator::getInstance().Action(arg);
   delete arg;
   return 0;
}
