#include "arguments.hpp"



Arguments::Arguments(const int argc, const char * const * const argv) :
   mode(*_mode),
   dataPath(*_dataPath),
   carrierPath(*_carrierPath),
   outputPath(*_outputPath)
{
   for (int i = 1; i < argc; i++)
   {
      auto arg = std::string(argv[i]);
      if (arg.find("-") != 0) // unnamed arguments
      {
         if (_mode == nullptr) _mode = parseMode(arg);
         else if (*_mode == Mode::hide && _dataPath == nullptr) _dataPath = new std::string(arg);
         else if (_carrierPath == nullptr) _carrierPath = new std::string(arg);
         else if (_outputPath == nullptr) _outputPath = new std::string(arg);
         else throw std::invalid_argument("too many command-line arguments");
      }
      else if (arg == "-m" || arg == "--mode")
      {
         if (_mode != nullptr) throw std::invalid_argument("mode provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("mode argument value missing");
         _mode = parseMode(std::string(argv[i++]));
      }
      else if (arg == "-d" || arg == "--data")
      {
         if (_dataPath != nullptr) throw std::invalid_argument("data path provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("data path argument value missing");
         _dataPath = new std::string(argv[i++]);
      }
      else if (arg == "-c" || arg == "--carrier")
      {
         if (_carrierPath != nullptr) throw std::invalid_argument("carrier path provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("carrier path argument value missing");
         _carrierPath = new std::string(argv[i++]);
      }
      else if (arg == "-o" || arg == "--output")
      {
         if (_outputPath != nullptr) throw std::invalid_argument("output path provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("output path argument value missing");
         _outputPath = new std::string(argv[i++]);
      }
   }

   // validity & completeness checks
   if (_mode == nullptr) throw std::invalid_argument("mode not provided");
   if (*_mode == Mode::hide)
   {
      if (_dataPath == nullptr) throw std::invalid_argument("data path not provided");
   }
   else
   {
      if (_dataPath != nullptr) throw std::invalid_argument("data path provided with mode == unhide");
   }
   if (_carrierPath == nullptr) throw std::invalid_argument("carrier path not provided");
   if (_outputPath == nullptr) throw std::invalid_argument("output path not provided");
}



Arguments::Mode* Arguments::parseMode(const std::string& name)
{
   if (name == "hide") return new Mode(Mode::hide);
   if (name == "unhide") return new Mode(Mode::unhide);
   throw std::invalid_argument("mode not recognized");
}
