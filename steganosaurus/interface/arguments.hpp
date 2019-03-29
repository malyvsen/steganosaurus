#pragma once

#include <string>
#include <stdexcept>



class Arguments
{
public:
   Arguments();
   Arguments* Parse(const int argc, const char * const * const argv);

   enum class Mode {unknown = -1, write, read, clear};

   const Mode& mode;
   const std::string& dataPath; // only used with mode == write
   const std::string& carrierPath;
   const std::string& outputPath;

protected:
   Mode _mode = Mode::unknown;
   std::string _carrierPath = "";
   std::string _dataPath = "";
   std::string _outputPath = "";

private:
   static Mode _ParseMode(const std::string& name);
};
