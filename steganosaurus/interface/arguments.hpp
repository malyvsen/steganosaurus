#ifndef INTERFACE_ARGUMENTS
#define INTERFACE_ARGUMENTS

#include <string>
#include <stdexcept>



class Arguments
{
public:
   Arguments(const int argc, const char * const * const argv);

   enum class Mode {hide, unhide};

   const Mode& mode;
   const std::string& dataPath; // only used with mode == hide
   const std::string& carrierPath;
   const std::string& outputPath;

protected:
   Mode* _mode = nullptr;
   std::string* _carrierPath = nullptr;
   std::string* _dataPath = nullptr;
   std::string* _outputPath = nullptr;

private:
   Mode* parseMode(const std::string& name);
};



#endif // INTERFACE_ARGUMENTS
