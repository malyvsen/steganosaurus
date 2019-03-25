#ifndef INTERFACE_ARGUMENTS
#define INTERFACE_ARGUMENTS

#include <string>
#include <stdexcept>



class Arguments
{
public:
   Arguments(const int argc, const char * const * const argv);

   enum class Mode {unknown = -1, hide, unhide};

   const Mode& mode;
   const std::string& dataPath; // only used with mode == hide
   const std::string& carrierPath;
   const std::string& outputPath;

protected:
   Mode _mode = Mode::unknown;
   std::string _carrierPath = "";
   std::string _dataPath = "";
   std::string _outputPath = "";

private:
   static Mode parseMode(const std::string& name);
};



#endif // INTERFACE_ARGUMENTS
