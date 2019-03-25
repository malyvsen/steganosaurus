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
