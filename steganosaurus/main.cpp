#include "_include.hpp"



int main(int argc,char** argv)
{
   auto arguments = new Arguments();
   arguments->Parse(argc, argv);
   Communicator::getInstance().Action(arguments);
   delete arguments;
   return 0;
}
