#include "../catch.hpp"
#include "../../steganosaurus/interface/_include.hpp"


SCENARIO("arguments are passed correctly", "[interface]")
{
   GIVEN("hardcoded non-existent paths")
   {
      const char* programPath = "./program";
      const char* dataPath = "./data";
      const char* carrierPath = "./carrier";
      const char* outputPath = "./output";

      WHEN("mode is write")
      {
         WHEN("arguments are provided in order")
         {
            const char* argv[] = {programPath, "write", dataPath, carrierPath, outputPath};
            auto arguments = Arguments().Parse(5, argv);
            REQUIRE(arguments.mode == Arguments::Mode::write);
            REQUIRE(arguments.dataPath == dataPath);
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
         WHEN("arguments are provided in many different ways")
         {
            const char* argv[] = {programPath, "--mode", "write", "-c", carrierPath, dataPath, "-o", outputPath};
            auto arguments = Arguments().Parse(8, argv);
            REQUIRE(arguments.mode == Arguments::Mode::write);
            REQUIRE(arguments.dataPath == dataPath);
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
      }
      WHEN("mode is read")
      {
         WHEN("arguments are provided in order")
         {
            const char* argv[] = {programPath, "read", carrierPath, outputPath};
            auto arguments = Arguments().Parse(4, argv);
            REQUIRE(arguments.mode == Arguments::Mode::read);
            REQUIRE(arguments.dataPath == "");
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
         WHEN("arguments are provided in many different ways")
         {
            const char* argv[] = {programPath, "-m", "read", "--output", outputPath, carrierPath};
            auto arguments = Arguments().Parse(6, argv);
            REQUIRE(arguments.mode == Arguments::Mode::read);
            REQUIRE(arguments.dataPath == "");
            REQUIRE(arguments.carrierPath == carrierPath);
            REQUIRE(arguments.outputPath == outputPath);
         }
      }
   }
}

SCENARIO("arguments are not passed correctly", "[interface]")
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
         REQUIRE_THROWS(Arguments().Parse(1, argv));
      }

      WHEN("the mode is wrong")
      {
         const char* argv[] = {programPath, "encode", dataPath, carrierPath, outputPath};
         REQUIRE_THROWS(Arguments().Parse(5, argv));
      }

      WHEN("provided too many arguments")
      {
         const char* argv[] = {programPath, "-m", "write", "-c", carrierPath, "-d", dataPath, "-o", outputPath, "-f"};
         REQUIRE_THROWS(Arguments().Parse(10, argv));
      }

      WHEN("argument is provided more than once ")
      {
         const char* argv[] = {programPath, "-m", "read", "--output", outputPath, "-c", carrierPath, "--output", outputPath};
         REQUIRE_THROWS(Arguments().Parse(9, argv));
      }

      WHEN("data path is provided with read flag")
      {
         const char* argv[] = {programPath, "-m", "read", "-o", outputPath, "-c", carrierPath, "-d", dataPath};
         REQUIRE_THROWS(Arguments().Parse(9, argv));
      }
    }
}
