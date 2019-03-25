#include "arguments.hpp"



Arguments::Arguments(const int argc, const char * const * const argv) :
   mode(_mode),
   dataPath(_dataPath),
   carrierPath(_carrierPath),
   outputPath(_outputPath)
{
   for (int i = 1; i < argc; i++)
   {
      auto arg = std::string(argv[i]);
      if (arg.find("-") != 0) // unnamed arguments
      {
         if (_mode == Mode::unknown) _mode = parseMode(arg);
         else if (_mode == Mode::hide && _dataPath == "") _dataPath = std::string(arg);
         else if (_carrierPath == "") _carrierPath = std::string(arg);
         else if (_outputPath == "") _outputPath = std::string(arg);
         else throw std::invalid_argument("too many command-line arguments");
      }
      else if (arg == "-m" || arg == "--mode")
      {
         if (_mode != Mode::unknown) throw std::invalid_argument("mode provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("mode argument value missing");
         _mode = parseMode(std::string(argv[++i]));
      }
      else if (arg == "-d" || arg == "--data")
      {
         if (_dataPath != "") throw std::invalid_argument("data path provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("data path argument value missing");
         _dataPath = std::string(argv[++i]);
      }
      else if (arg == "-c" || arg == "--carrier")
      {
         if (_carrierPath != "") throw std::invalid_argument("carrier path provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("carrier path argument value missing");
         _carrierPath = std::string(argv[++i]);
      }
      else if (arg == "-o" || arg == "--output")
      {
         if (_outputPath != "") throw std::invalid_argument("output path provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("output path argument value missing");
         _outputPath = std::string(argv[++i]);
      }
   }

   // validity & completeness checks
   if (_mode == Mode::unknown) throw std::invalid_argument("mode not provided");
   if (_mode == Mode::hide)
   {
      if (_dataPath == "") throw std::invalid_argument("data path not provided");
   }
   else
   {
      if (_dataPath != "") throw std::invalid_argument("data path provided with mode == unhide");
   }
   if (_carrierPath == "") throw std::invalid_argument("carrier path not provided");
   if (_outputPath == "") throw std::invalid_argument("output path not provided");
}



Arguments::Mode Arguments::parseMode(const std::string& name)
{
   if (name == "hide") return Mode::hide;
   if (name == "unhide") return Mode::unhide;
   throw std::invalid_argument(std::string("mode ") + name + std::string(" not recognized"));
}