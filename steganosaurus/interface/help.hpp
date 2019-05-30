#pragma once

#include <string>
#include <iostream>



namespace Help
{
    void Display();

    const std::string message =
    "steganosaurus v0.3.1\n"
    "options:\n"
    "-m, --mode\tspecify mode: write/read/clear/help\n"
    "-h, --help\tdisplay this message and quit\n"
    "-d, --data\tspecify path to file with data to write\n"
    "-c, --carrier\tspecify path to file with image to hide data in\n"
    "-o, --output\tspecify path to file which will be output";
};
