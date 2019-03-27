#include <test/catch.hpp>
#include "../../steganosaurus/interface/arguments.cpp"


SCENARIO("arguments are parsed correctly", "[interface]")
{
   GIVEN("hardcoded non-existent paths")
   {
      const char* programPath = "./program";
      const char* dataPath = "./data";
      const char* carrierPath = "./carrier";
      const char* outputPath = "./output";

      WHEN("mode is hide")
      {
         WHEN("arguments are provided in order")
         {
            const char* argv[] = {programPath, "hide", dataPath, carrierPath, outputPath};
            auto arguments = Arguments(5, argv);
            REQUIRE(arguments.mode == Arguments::Mode::hide);
            REQUIRE(arguments.dataPath == dataPath);
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
         WHEN("arguments are provided in many different ways")
         {
            const char* argv[] = {"./program", "--mode", "hide", "-c", "./carrier", "./data", "-o", "./output"};
            auto arguments = Arguments(8, argv);
            REQUIRE(arguments.mode == Arguments::Mode::hide);
            REQUIRE(arguments.dataPath == dataPath);
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
      }
      WHEN("mode is unhide")
      {
         WHEN("arguments are provided in order")
         {
            const char* argv[] = {programPath, "unhide", carrierPath, outputPath};
            auto arguments = Arguments(4, argv);
            REQUIRE(arguments.mode == Arguments::Mode::unhide);
            REQUIRE(arguments.dataPath == "");
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
         WHEN("arguments are provided in many different ways")
         {
            const char* argv[] = {programPath, "-m", "unhide", "--output", outputPath, carrierPath};
            auto arguments = Arguments(6, argv);
            REQUIRE(arguments.mode == Arguments::Mode::unhide);
            REQUIRE(arguments.dataPath == "");
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
      }
   }
}

SCENARIO("arguments are not parsed correctly", "[interface]")
{

   GIVEN("hardcoded non-existent paths")
   {
      const char* programPath = "./program";
      const char* dataPath = "./data";
      const char* carrierPath = "./carrier";
      const char* outputPath = "./output";

      WHEN("arguments are not provided")
      {
         const char* argv[] = {programPath};
         REQUIRE_THROWS(Arguments(1, argv));
      }

      WHEN("the mode is wrong")
      {
         const char* argv[] = {programPath, "encode", dataPath, carrierPath, outputPath};
         REQUIRE_THROWS(Arguments(5, argv));
      }
//      FIXME
//      WHEN("provided too many arguments")
//      {
//         const char* argv[] = {programPath, "-m", "hide", "-c", carrierPath, "-d", dataPath, "-o", outputPath, "-f"};
//         REQUIRE_THROWS(Arguments(10, argv));
//      }

      WHEN("argument is provided more than once ")
      {
         const char* argv[] = {programPath, "-m", "unhide", "--output", outputPath, "-c", carrierPath, "--output", outputPath};
         REQUIRE_THROWS(Arguments(9, argv));
      }

      WHEN("data path is provided with unhide flag")
      {
         const char* argv[] = {programPath, "-m", "unhide", "-o", outputPath, "-c", carrierPath, "-d", dataPath};
         REQUIRE_THROWS(Arguments(9, argv));
      }
    }
}
