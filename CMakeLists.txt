cmake_minimum_required(VERSION 3.13)
project(steganosaurus)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(steganosaurus)
include_directories(steganosaurus/communicator)
include_directories(steganosaurus/communicator/encoders)
include_directories(steganosaurus/interface)
include_directories(test)
include_directories(test/interface)

add_executable(steganosaurus
        steganosaurus/communicator/encoders/iencoder.cpp
        steganosaurus/communicator/encoders/iencoder.h
        steganosaurus/communicator/encoders/simpleencoder.cpp
        steganosaurus/communicator/encoders/simpleencoder.h
        steganosaurus/communicator/commyunicator.cpp
        steganosaurus/communicator/commyunicator.h
        steganosaurus/interface/arguments.cpp
        steganosaurus/interface/arguments.hpp)

add_executable(test test/main.cpp)