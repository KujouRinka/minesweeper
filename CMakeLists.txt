cmake_minimum_required(VERSION 3.16)
project(minesweeper)

set(CMAKE_CXX_STANDARD 11)

add_executable(minesweeper main.cpp src/MapGenerator/randomMine.cpp src/MapGenerator/MapGenerator.h src/Controller/Controller.h src/History/History.h src/Controller/baseControl.cpp src/MapGenerator/MapOperation.cpp src/Controller/ControllerOperation.cpp)