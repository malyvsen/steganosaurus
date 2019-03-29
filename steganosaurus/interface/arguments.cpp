#include "arguments.hpp"



Arguments::Arguments() : mode(_mode), dataPath(_dataPath), carrierPath(_carrierPath), outputPath(_outputPath) {}



Arguments& Arguments::Parse(const int argc, const char * const * const argv)
{
   for (int i = 1; i < argc; i++)
   {
      auto arg = std::string(argv[i]);
      if (arg.find("-") != 0) // unnamed arguments
      {
         if (_mode == Mode::unknown) _mode = _ParseMode(arg);
         else if (_mode == Mode::write && _dataPath == "") _dataPath = std::string(arg);
         else if (_carrierPath == "") _carrierPath = std::string(arg);
         else if (_outputPath == "") _outputPath = std::string(arg);
         else throw std::invalid_argument("too many command-line arguments");
      }
      else if (arg == "-m" || arg == "--mode")
      {
         if (_mode != Mode::unknown) throw std::invalid_argument("mode provided more than once");
         if (i + 1 >= argc) throw std::invalid_argument("mode argument value missing");
         _mode = _ParseMode(std::string(argv[++i]));
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
      else throw std::invalid_argument(std::string("unrecognized argument: ") + arg);
   }

   // validity & completeness checks
   if (_mode == Mode::unknown) throw std::invalid_argument("mode not provided");
   if (_mode == Mode::write)
   {
      if (_dataPath == "") throw std::invalid_argument("data path not provided");
   }
   else
   {
      if (_dataPath != "") throw std::invalid_argument("data path provided with mode == read");
   }
   if (_carrierPath == "") throw std::invalid_argument("carrier path not provided");
   if (_outputPath == "") throw std::invalid_argument("output path not provided");

   return *this;
}



Arguments::Mode Arguments::_ParseMode(const std::string& name)
{
   if (name == "write") return Mode::write;
   if (name == "read") return Mode::read;
   if (name == "clear") return Mode::clear;
   throw std::invalid_argument(std::string("\"") + name + std::string("\" is not a valid mode"));
}
