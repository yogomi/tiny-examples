cmake_minimum_required(VERSION 3.2)
project(StructMemory)

list(APPEND CMAKE_CXX_FLAGS "-std=c++1z ${CMAKE_CXX_FLAGS}")

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.10)

add_executable(struct_memory main.cpp)
