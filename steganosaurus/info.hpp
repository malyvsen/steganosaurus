#pragma once

#include <string>



namespace Info
{
    const std::string programName = "steganosaurus";
    const std::string version = "0.3.1";
    const std::string detailedVersion = version + ", built " + __DATE__ + " at " + __TIME__;
    const std::string help =
    programName + " " + detailedVersion + "\n" +
    "options:\n"
    "-m, --mode\tspecify mode: write/read/clear/version/help\n"
    "-v, --version\tdisplay program version and quit\n"
    "-h, --help\tdisplay this message and quit\n"
    "-d, --data\tspecify path to file with data to write\n"
    "-c, --carrier\tspecify path to file with image to hide data in\n"
    "-o, --output\tspecify path to file which will be output";
};
