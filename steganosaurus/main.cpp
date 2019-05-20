#include "_include.hpp"
#include <QApplication>


int main(int argc,char** argv)
{
   try 
   {
        Arguments * arguments = new Arguments();
        if(argc == 1)
        {
            QApplication qtApp(argc, argv);
            QtInterface gui(&arguments);
            gui.show();
            int ret = qtApp.exec();
        }
        else
        {
            arguments->Parse(argc, argv);
        }
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
