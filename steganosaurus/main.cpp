#include "_include.hpp"


int main(int argc,char** argv)
{
   try
   {
        Arguments* arguments = new Arguments();
        #ifdef GUI
            QApplication qtApp(argc, argv);
            QtInterface gui(&arguments);
            gui.show();
            int ret = qtApp.exec();
        #else
            arguments->Parse(argc, argv);
            Communicator::getInstance().Action(arguments);
        #endif
        delete arguments;
   }
   catch (std::invalid_argument e)
   {
        std::cout << "error: " << e.what() << '\n';
        return 1;
   }

   return 0;
}
