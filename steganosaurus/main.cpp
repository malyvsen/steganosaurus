#include "_include.hpp"



int main(int argc,char** argv)
{
   try 
   {
        auto arguments = new Arguments();
        arguments->Parse(argc, argv);
        Communicator::getInstance().Action(arguments);
        delete arguments;
   }
   catch (std::invalid_argument e) 
   {
        std::cout << "error: " << e.what() << '\n';
        return 1;
   }
   
   return 0;
}
