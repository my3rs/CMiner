cmake_minimum_required(VERSION 3.9)
project(CMiner)

set(CMAKE_CXX_STANDARD 11)

add_executable(CMiner src/main.cpp src/CMiner/CMinerBase.cpp src/CMiner/CMinerBase.h src/CMiner/Rule.cpp src/CMiner/Rule.h)

add_executable(cmainer_test src/CMiner/test.cpp)